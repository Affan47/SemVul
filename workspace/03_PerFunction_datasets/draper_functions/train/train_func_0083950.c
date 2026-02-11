cha_check_table_for_undef(int hinsi)
{
    int i;

    for (i = 0; i < tbl_num; i++)
	if (rensetu_tbl[i].hinsi == hinsi)
	    if (!rensetu_tbl[i].goi)
		return i;

    return -1;
}
