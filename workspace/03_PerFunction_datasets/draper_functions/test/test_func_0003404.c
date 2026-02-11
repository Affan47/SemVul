reprocess_filter_patterns(MAILSTREAM *stream, MSGNO_S *msgmap, int flags)
{
    if(stream){
	long i;
	int  exbits;

	if(msgno_include(stream, msgmap, flags)
	   && stream == ps_global->mail_stream
	   && !(flags & MI_CLOSING)){
	    clear_index_cache(stream, 0);
	    refresh_sort(stream, msgmap, SRT_NON);
	    ps_global->mangled_header = 1;
	}


	process_filter_patterns(stream, msgmap,
				(flags & MI_STATECHGONLY) ? 1L : 0);


	for(i = 1; i <= stream->nmsgs; i++){
	    if(msgno_exceptions(stream, i, "0", &exbits, FALSE)){
		if(exbits & MSG_EX_STATECHG){
		    exbits &= ~MSG_EX_STATECHG;
		    msgno_exceptions(stream, i, "0", &exbits, TRUE);
		}
	    }
	}
    }
}
