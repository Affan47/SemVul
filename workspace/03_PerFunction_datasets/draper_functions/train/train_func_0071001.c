findMatches(const char *seq, int len, reportMatch report)
{
    if (root) {
        int new_len;
        int *uni2real = (int*)malloc(len*sizeof(int));
        char *uni_seq = uni2real ? unify_sequence(seq, len, &new_len, &uni2real) : NULL;

        if (uni_seq) {
            int off;
            char *useq = uni_seq;
            int mismatch_list[MAX_MISMATCHES];

            for (off=0; off<MAX_MISMATCHES; off++) {
                mismatch_list[off] = -1;
            }

            SearchTreeNode::set_report(report, uni2real);
            SearchTreeNode::set_mismatches(sett->get_min_mismatches(), sett->get_max_mismatches());

            for (off=0; off<new_len && !ignore_more_results; off++,useq++) {
                SearchTreeNode::set_start_offset(off);
                root->findMatches(off, useq, new_len-off, 0, mismatch_list);
            }

            free(uni_seq);
            free(uni2real);
        }
        else {
            aw_message("Out of swapspace?");
            if (uni2real) free(uni2real);
        }
    }
}
