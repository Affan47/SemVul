stlg_nmembers(const SuperTlg *stlg)
{
    if (stlg_is_tlg(stlg))
        return 0;

    if (stlg_is_sb(stlg))
        return 1;

    return list_length(stlg->members);
}
