def_special(
    DEFBUF *    defp
)


{
    const FILEINFO *    file;
    DEFBUF **   prevp;
    int         cmp;

    switch (defp->nargs) {
    case DEF_NOARGS_DYNAMIC - 1:
        if ((src_line > std_limits.line_num || src_line <= 0)
                && (warn_level & 1))
            diag_macro( CWARN
                    , "Line number %.0s\"%ld\" is out of range"
                    , NULL, src_line, NULL, defp, NULL);
        sprintf( defp->repl, "%ld", src_line);
        break;
    case DEF_NOARGS_DYNAMIC - 2:
        for (file = infile; file != NULL; file = file->parent) {
            if (file->fp != NULL) {
                sprintf( work_buf, "\"%s\"", file->filename);
                if (str_eq( work_buf, defp->repl))
                    break;
                defp->nargs = DEF_NOARGS;
                prevp = look_prev( defp->name, &cmp);
                defp = install_macro( "__FILE__", DEF_NOARGS_DYNAMIC - 2, ""
                        , work_buf, prevp, cmp, 0);
                break;
            }
        }
        break;
    }
    return  defp;
}
