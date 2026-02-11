fp_find_flush(void)
{
    static string_ty *dot;
    fp_subdir_ty    *sdp;

    if (!option_test(OPTION_FINGERPRINT_WRITE))
    {
        trace(("no fp write\n"));
        return;
    }


    trace(("fp_find_flush()\n{\n"));
    need_to_write_dot = 0;
    if (subdir_stp)
        symtab_walk(subdir_stp, subdir_walk, 0);


    if (!dot)
        dot = str_from_c(".");
    sdp = fp_find_subdir(dot, 0);
    if (need_to_write_dot)
        sdp->dirty = 1;
    fp_subdir_write(sdp, &need_to_write_dot);
    trace(("}\n"));
}
