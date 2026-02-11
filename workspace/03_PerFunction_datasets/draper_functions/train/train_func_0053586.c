gf_terminal(FILTER_S *f, int flg)
{
    if(flg == GF_DATA){
	GF_INIT(f, f);

	while(op < eob)
	  if((*last_filter)(*op++) <= 0)
	    gf_error(errno ? error_description(errno) : "Error writing pipe");

	GF_CH_RESET(f);
    }
    else if(flg == GF_RESET)
      errno = 0;
}
