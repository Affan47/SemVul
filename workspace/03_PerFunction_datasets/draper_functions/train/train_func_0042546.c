genbank_skip_unidentified(line, fp, blank_num)
     char        *line;
     FILE_BUFFER  fp;
     int    blank_num;
{
    char    *eof;


    for(eof=Fgetline(line, LINENUM, fp);
        eof!=NULL&&genbank_check_blanks(line, blank_num);
        eof=Fgetline(line, LINENUM, fp))    ;

    return(eof);
}
