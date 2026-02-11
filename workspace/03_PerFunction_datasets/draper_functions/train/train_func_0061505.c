dec_mts_table(int mtsno,
                       IntSet   mt_tmp,
                       IntSet   fork_tmp,
                       Stasche_pc_info_tmp *pc_info_tmp)
{
    Mts_tmp *rpt = NULL;
    Stasche_mts_table *mtspt = NULL;
    Stasche_pc_info **pc_info = NULL;
    int i;

    rpt = (Mts_tmp *)calloc(1, sizeof(Mts_tmp));
    if (rpt == NULL) {
        fprintf(stderr, "No more room for Mts_tmp.\n");
        exit(-1);
    }
    rpt->mts_tbl = NULL;
    rpt->mt      = NULL;
    rpt->fork    = NULL;
    rpt->next    = NULL;

    mtspt = (Stasche_mts_table *)calloc(1, sizeof(Stasche_mts_table));
    if (mtspt == NULL) {
        fprintf(stderr, "No more room for Stasche_mts_table.\n");
        exit(-1);
    }
    mtspt->pc_info = NULL;
    mtspt->no = mtsno;
    mtspt->pc_num = pc_num;

    if (pc_info_tmp != NULL) {
        pc_info = (Stasche_pc_info **)calloc(pc_num, sizeof(Stasche_pc_info *));
        if (pc_info == NULL) {
            fprintf(stderr, "No more room for Stasche_pc_info.\n");
            exit(-1);
        }

        for (i = 0; i < pc_num; i++) {
            *(pc_info + i) = pc_info_tmp->pc_info;
            pc_info_tmp = pc_info_tmp->next;
	}
        mtspt->pc_info = pc_info;
    }

    rpt->mts_tbl = mtspt;
    if(mt_tmp  !=NULL) rpt->mt   = mt_tmp;
    if(fork_tmp!=NULL) rpt->fork = fork_tmp;

    return rpt;
}
