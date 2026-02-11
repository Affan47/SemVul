fold_line(name)
     char *name;
{
    column = 0;
    printf(") s\n");
    if (++line >= linesperpage) {
        endpage();
        skip_page();
        if (first_page && is_binaryfile(name))
            return FALSE;
        line = 0;
    }
    if (numbering)
        printf("(    +");
    else
        printf("( ");

    return TRUE;
}
