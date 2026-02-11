addachar(char c)
{
  if(cmdline_used>=cmdline_allocated) {
    if(!cmdline_allocated) cmdline_allocated=128;
    while(cmdline_allocated<=cmdline_used)
      cmdline_allocated<<=1;
    if(cmdline!=NULL)
      cmdline=realloc(cmdline, cmdline_allocated);
    else
      cmdline=malloc(cmdline_allocated);
  }
  cmdline[cmdline_used++]=c;
}
