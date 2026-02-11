dbg_pfx(void){I idx=dbg_depth-1,i;
  idx=MIN(99,4+MAX(0,idx)*dbg_ti);memset(trcb,' ',idx);trcb[idx]='\0';
  if(dbg_ch!=' ')for(i=0;i<dbg_depth-1;++i)trcb[4+(i*dbg_ti)]=dbg_ch;
  R trcb;
}
