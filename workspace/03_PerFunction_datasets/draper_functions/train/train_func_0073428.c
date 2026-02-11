initial_fvstate_is_off(const Hmdf_context *hcx)
{
    Stasche_table *st_ptr;
    Stasche_pc_info *pc_info;

    st_ptr = get_stasche_table_from_hmdf_table(hcx->hmdf);

    if (st_ptr == NULL)
	fatal("MT schedule table not found\n");

    if (st_ptr->mts_num != 1)
	fatal("Numbers of SSMTG must be 1\n");

    if (hcx->pc_no > 0) {
        pc_info = st_ptr->mts[1]->pc_info[hcx->pc_no];

        return (pc_info != NULL && pc_info->fvc_type == POWER_OFF_START);
    }
    return FALSE;
}
