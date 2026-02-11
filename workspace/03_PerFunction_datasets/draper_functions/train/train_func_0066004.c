smi_load_doc_map(SegmentMergeInfo *smi)
{
    BitVector *deleted_docs = smi->deleted_docs;
    const int max_doc = smi->max_doc;
    int j = 0, i;

    smi->doc_map = ALLOC_N(int, max_doc);
    for (i = 0; i < max_doc; i++) {
        if (bv_get(deleted_docs, i)) {
            smi->doc_map[i] = -1;
        }
        else {
            smi->doc_map[i] = j++;
        }
    }
    smi->doc_cnt = j;
}
