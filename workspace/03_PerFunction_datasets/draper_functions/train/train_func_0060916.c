do_inline(char *line,int *res,struct session *ses)
{
    char command[BUFFER_SIZE],*ptr;

    ptr=command;
    while (*line&&(*line!=' '))
        *ptr++=*line++;
    *ptr=0;
    line=space_out(line);


    if (is_abrev(command,"finditem"))
        *res=finditem_inline(line,ses);
    else if (is_abrev(command,"isatom"))
        *res=isatom_inline(line,ses);
    else if (is_abrev(command,"listlength"))
        *res=listlength_inline(line,ses);
    else if (is_abrev(command,"strlen"))
        *res=strlen_inline(line,ses);
    else if (is_abrev(command,"random"))
        *res=random_inline(line,ses);
    else if (is_abrev(command,"grep"))
        *res=grep_inline(line,ses);
    else if (is_abrev(command,"strcmp"))
        *res=strcmp_inline(line,ses);
    else if (is_abrev(command,"match"))
        *res=match_inline(line,ses);
    else if (is_abrev(command,"ord"))
        *res=ord_inline(line,ses);
    else
    {
        tintin_eprintf(ses,"#Unknown inline command [%c%s]!",tintin_char,command);
        return 0;
    };

    return 1;
}
