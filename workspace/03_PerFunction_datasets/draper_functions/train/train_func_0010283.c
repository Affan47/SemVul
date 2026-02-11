gt_match_iterator_blast_file_new(const char *matchfile,
                                                  GtError *err)
{
  GtMatchIterator *mp;
  GtMatchIteratorBlast *mpb;
  mp = gt_match_iterator_create(gt_match_iterator_blast_class());
  mpb = gt_match_iterator_blast_cast(mp);
  mpb->pvt = gt_calloc(1, sizeof (GtMatchIteratorBlastMembers));
  GtFileMode mode;

  if (gt_file_exists(matchfile)) {
    mode = gt_file_mode_determine(matchfile);
    if (mode == GT_FILE_MODE_UNCOMPRESSED) {
      mpb->pvt->matchfilep = fopen(matchfile, "r");
      mpb->pvt->gtmatchfilep = NULL;
      if (!mpb->pvt->matchfilep) {
        gt_error_set(err, "could not open %s", matchfile);
        return NULL;
      }
    } else {
      mpb->pvt->gtmatchfilep = gt_file_open(mode, matchfile, "r", err);
      mpb->pvt->matchfilep = NULL;
      if (!mpb->pvt->gtmatchfilep)
        return NULL;
    }
    mpb->pvt->matchfile = matchfile;
    mpb->pvt->process = false;
    return mp;
  } else {
    gt_error_set(err, "no such file or directory %s", matchfile);
    return NULL;
  }
}
