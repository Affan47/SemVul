check_bases(const char *old_sequence, int old_len, const char *new_sequence, int new_len, int start_pos, int end_pos) {
    ED4_manager *walk_up = this;

#ifdef DEBUG
    if (end_pos==-1) {
        printf("check_bases does not know update range - maybe an error?\n");
    }
#endif

    if (old_sequence) {
        if (new_sequence) {
            if (end_pos==-1) {
                if (!ED4_char_table::changed_range(old_sequence, new_sequence, min(old_len, new_len), &start_pos, &end_pos)) {
                    return ED4_R_OK;
                }
            }

#if defined(DEBUG) && 0
            printf("check_bases(..., %i, %i)\n", start_pos, end_pos);
#endif

            WITH_ALL_ABOVE_GROUP_MANAGER_TABLES(walk_up, sub_and_add(old_sequence, new_sequence, start_pos, end_pos));
        } else {
            e4_assert(start_pos==0 && end_pos==-1);
            WITH_ALL_ABOVE_GROUP_MANAGER_TABLES(walk_up, sub(old_sequence, old_len));
        }
    } else {
        if (new_sequence) {
            e4_assert(start_pos==0 && end_pos==-1);
            WITH_ALL_ABOVE_GROUP_MANAGER_TABLES(walk_up, add(new_sequence, new_len));
        } else {
            return ED4_R_OK;
        }
    }

    ED4_ROOT->root_group_man->remap()->mark_compile_needed();
    return ED4_R_OK;
}
