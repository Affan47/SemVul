iw_merge_segments(IndexWriter *iw, const int min_seg,
                              const int max_seg)
{
    int i;
    SegmentInfos *sis = iw->sis;
    SegmentInfo *si = sis_new_segment(sis, 0, iw->store);

    SegmentMerger *merger = sm_create(iw, si, &sis->segs[min_seg],
                                      max_seg - min_seg);


    si->doc_cnt = sm_merge(merger);

    mutex_lock(&iw->store->mutex);

    for (i = min_seg; i < max_seg; i++) {
        si_delete_files(sis->segs[i], iw->fis, iw->deleter);
    }
    deleter_commit_pending_deletions(iw->deleter);

    sis_del_from_to(sis, min_seg, max_seg);

    if (iw->config.use_compound_file) {
        iw_commit_compound_file(iw, si);
        si->use_compound_file = true;
    }

    sis_write(sis, iw->store, iw->deleter);

    mutex_unlock(&iw->store->mutex);

    sm_destroy(merger);
}
