Update(void *data, int arg)
{
 if(*(uint8 *)data)
 {
  *(uint8 *)data=0;
  seq=ptr=0;
  have=1;
  strcpy(bdata,(uint8 *)data+1);
  strcpy(&bdata[13],"SUNSOFT");
 }
}
