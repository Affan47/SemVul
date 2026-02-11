ogg_stream_pageout_fill(ogg_stream_state *os, ogg_page *og, int nfill){
  int force=0;
  if(ogg_stream_check(os)) return 0;

  if((os->e_o_s&&os->lacing_fill) ||
     (os->lacing_fill&&!os->b_o_s))
    force=1;

  return(ogg_stream_flush_i(os,og,force,nfill));
}
