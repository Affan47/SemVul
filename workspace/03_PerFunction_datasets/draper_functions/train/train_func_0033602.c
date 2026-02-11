FCEUD_SendData(void *data, uint32 len)
{
 int check;
 if(!ioctl(fileno(stdin),FIONREAD,&check))
 if(check)
 {
  char buf[1024];
  char *f;
  fgets(buf,1024,stdin);
  if((f=strrchr(buf,'\n')))
   *f=0;
  FCEUI_NetplayText(buf);
 }
 send(Socket, data, len ,0);
 return(1);
}
