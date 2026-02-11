CmdMultiCol(int code)


{
    long numCol, i;
    char *num, *format, *content, *bcontent;

    num = getBraceParam();
    format = getBraceParam();
    bcontent = getBraceParam();

    content = strdup_noendblanks(bcontent);
    free(bcontent);

    diagnostics(4, "CmdMultiCol cols=%s format=<%s> content=<%s>", num, format, content);
    numCol = atoi(num);
    free(num);

    diagnostics(4, "Entering Convert() from CmdMultiCol()");
    ConvertString(content);
    diagnostics(4, "Exiting Convert() from CmdMultiCol()");

    for (i = 1; i < numCol; i++) {
        fprintRTF("\\cell}\n");
        fprintRTF("{\\pard\\intbl");
    }

    free(content);
    free(format);
}
