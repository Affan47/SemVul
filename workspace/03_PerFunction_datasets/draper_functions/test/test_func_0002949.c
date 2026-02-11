skip_script_line(osfildef *fp)
{
    int c;


    for (c = osfgetc(fp) ; c != EOF && c != '\n' && c != '\r' ;
         c = osfgetc(fp)) ;
}
