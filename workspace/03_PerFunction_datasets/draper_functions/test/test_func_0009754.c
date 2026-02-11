stasche_write_decl_vars(fsbe_context *cx, Hmdf_table *hmdf)
{
    int mtg_id = hmdf->mtg_id;
    int sync_num
	= get_stasche_table_from_hmdf_table(hmdf)->max_sync_num;
    int i, j;

    fsbe_printf(cx, "C == VARIABLE FOR STATIC SCHEDULER ");
    fsbe_printf(cx, "FOR H%d ==\n", mtg_id);

    for (i = 0; i < hmdf->pc_num; i++) {
        for (j = 0; j < hmdf->pe_num; j++) {
            ompfbe_iprintf(cx, "INTEGER SS_MTG_COUNT%d_PC%d_PE%d\n", mtg_id, i, j);
            ompfbe_iprintf(cx, "SAVE SS_MTG_COUNT%d_PC%d_PE%d\n", mtg_id, i, j);
        }
    }

    if(ompfbe_get_mtg_table_from_mtg_id(mtg_id)->end_num > 1)
	ompfbe_iprintf(cx, "INTEGER STASCHE_EMT%d(0:%d,0:%d)\n",
		       mtg_id, hmdf->pc_num - 1, hmdf->pe_num - 1);

    if(sync_num > 0)
	ompfbe_iprintf(cx, "INTEGER STASCHE_FLG%d(%d)\n", mtg_id, sync_num);

#ifdef MTS_END_BARRIER
    ompfbe_iprintf(cx, "INTEGER STASCHE_END_FLAG%d(0:%d,0:%d)\n",
		   mtg_id, hmdf->pc_num - 1, hmdf->pc_num - 1);
#endif

    ompfbe_iprintf(cx, "INTEGER SCHE_FLG%d(0:%d,0:%d)\n",
		   mtg_id, hmdf->pc_num - 1, hmdf->pe_num - 1);
}
