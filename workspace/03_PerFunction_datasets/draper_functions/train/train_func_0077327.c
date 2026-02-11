gifti_disp_lib_hist(void)
{
   int c, len = sizeof(gifti_history)/sizeof(char *);
   for( c = 0; c < len; c++ )
       fputs(gifti_history[c], stdout);
}
