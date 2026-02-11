cwirc_is_cw_frame(char *frame)
{
  char *ptr,*ptr2;
  char buf[7];
  T_U8 evts_fmt;
  int i,j,k;

  ptr=frame;


  if(!strncmp(ptr,EXPLICIT_CALLSIGN_HEADER,strlen(EXPLICIT_CALLSIGN_HEADER)))
  {

    if((ptr=strchr(ptr,','))==NULL)
      return(0);
    else
      ptr++;
  }


  if(!strncmp(ptr,GRID_SQUARE_HEADER,strlen(GRID_SQUARE_HEADER)))
  {

    if((ptr2=strchr(ptr,','))==NULL)
      return(0);
    else
    {
      ptr+=strlen(GRID_SQUARE_HEADER);


      if(ptr2-ptr!=4 && ptr2-ptr!=6)

        return(0);


      strncpy(buf,ptr,ptr2-ptr);
      buf[ptr2-ptr]=0;
      rot46_enc_dec(buf);
      if(!cwirc_is_grid_square(buf))

        return(0);

      ptr=ptr2+1;
    }
  }


  if(strncmp(ptr,CW_FRAME_HEADER_BASEFMT,strlen(CW_FRAME_HEADER_BASEFMT)) &&
	strncmp(ptr,CW_FRAME_HEADER_XFMT,strlen(CW_FRAME_HEADER_XFMT)))
    return(0);


  if(ptr[1]=='w')
  {
    evts_fmt=0;
    ptr+=strlen(CW_FRAME_HEADER_BASEFMT);


    if(strlen(ptr)<4 || strlen(ptr)%2)
      return(0);
  }
  else
  {
    evts_fmt=1;
    ptr+=strlen(CW_FRAME_HEADER_XFMT);


    if(strlen(ptr)<3)
      return(0);
  }


  for(i=0;i<strlen(ptr);i++)
    if(ptr[i]<'!' || ptr[i]>'~')
      return(0);


  ptr+=2;
  k=0;
  while(k<XMIT_BUF_DELAY*1.5 && ptr[0])
  {
    j=evts_fmt==0?decoded_number_basefmt(&ptr):decoded_number_xfmt(&ptr);
    if(!j || (j<0?-j:j)>=XMIT_BUF_DELAY*1.5)
      return(0);
    k+=j<0?-j:j;
  }
  if(k>=XMIT_BUF_DELAY*1.5)
    return(0);

  return(1);
}
