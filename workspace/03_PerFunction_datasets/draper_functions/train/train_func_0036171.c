get_stasche_pcnumber_from_mtno(const Stasche_table *st_ptr, int __mt_no)
{
    Stasche_mts_table  *mts_ptr;
    Stasche_pc_info  *pc_ptr;
    int  i, j;

    for (i = 1; i <= st_ptr->mts_num; i++) {
        mts_ptr = st_ptr->mts[i];
        for (j = 0; j < mts_ptr->pc_num; j++) {
            for (pc_ptr = mts_ptr->pc_info[j];
                 pc_ptr != NULL;
                 pc_ptr = pc_ptr->next) {
                if (pc_ptr->mt_number == __mt_no) {
                    return j;
                }
            }
        }
    }
    return -1;
}
