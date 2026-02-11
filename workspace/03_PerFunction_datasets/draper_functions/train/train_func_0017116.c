do_write(p)
char *p;
{
 uword len;


 while (*p!=' ' && *p!=EOS) p++;
 while (*p==' ') p++;


 len=strlen(p);
 if ((*p != '\"') || (p[len-1] != '\"') || len<2)
   {
    wl_sj("W: The argument to WRITE should be delimited by double quotes.");
    wl_sj(p);
    num_war++;
    return;
   }


 p[len-1]=EOS;
 wl_sj(p+1);
 p[len-1]='\"';
}
