gs_currentcharmatrix(gs_state * pgs, gs_matrix * ptm, bool force)
{
    if (!pgs->char_tm_valid) {
        int code;

        if (!force)
            return_error(gs_error_undefinedresult);
        code = gs_setcharmatrix(pgs, &pgs->font->FontMatrix);
        if (code < 0)
            return code;
    }
    if (ptm != NULL)
        *ptm = char_tm_only(pgs);
    return 0;
}
