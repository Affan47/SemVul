rd_open_remote(REMDATA_S *rd)
{
    long openmode = SP_USEPOOL | SP_TEMPUSE;

    dprint((7, "rd_open_remote \"%s\"\n",
	   (rd && rd->rn) ? rd->rn : "?"));

    if(!rd)
      return;

    if(rd_stream_exists(rd)){
	rd->last_use = get_adj_time();
	return;
    }

    switch(rd->type){
      case RemImap:

	if(rd->access == ReadOnly)
	  openmode |= OP_READONLY;

	ps_global->noshow_error = 1;
	rd->t.i.stream = context_open(NULL, NULL, rd->rn, openmode, NULL);
	ps_global->noshow_error = 0;


	if(!rd->t.i.stream)
	  rd->flags |= USER_SAID_NO;

	if(rd->t.i.stream && rd->t.i.stream->halfopen){

	    rd_close_remote(rd);
	}

	if(rd->t.i.stream)
	  rd->last_use = get_adj_time();

	break;

      default:
	q_status_message(SM_ORDER, 3, 5, "rd_open_remote: type not supported");
	break;
    }
}
