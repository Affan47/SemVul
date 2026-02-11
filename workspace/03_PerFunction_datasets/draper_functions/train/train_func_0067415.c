get_msgno_by_msg_id(MAILSTREAM *stream, char *message_id, MSGNO_S *msgmap)
{
    SEARCHPGM  *pgm = NULL;
    long        hint = mn_m2raw(msgmap, mn_get_cur(msgmap));
    long        newmsgno = -1L;
    int         iter = 0;
    MESSAGECACHE *mc;
    extern MAILSTREAM *mm_search_stream;
    extern long        mm_search_count;

    if(!(message_id && message_id[0]) || stream->nmsgs < 1L)
      return(newmsgno);

    mm_search_count = 0L;
    mm_search_stream = stream;
    while(mm_search_count == 0L && iter++ < 3
	  && (pgm = mail_newsearchpgm()) != NULL){
	pgm->message_id = mail_newstringlist();
	pgm->message_id->text.data = (unsigned char *) cpystr(message_id);
	pgm->message_id->text.size = strlen(message_id);

	if(iter > 1 || hint > stream->nmsgs)
	  iter++;

	if(iter == 1){

	    pgm->msgno = mail_newsearchset();
	    pgm->msgno->first = pgm->msgno->last = hint;
	}
	else if(iter == 2){

	    pgm->msgno = mail_newsearchset();
	    if(stream->nmsgs > 100L)
	      pgm->msgno->first = stream->nmsgs-50L;
	    else{
		pgm->msgno->first = 1L;
		iter++;
	    }

	    pgm->msgno->last = stream->nmsgs;
	}

	pine_mail_search_full(stream, NULL, pgm, SE_NOPREFETCH | SE_FREE);

	if(mm_search_count){
	    for(newmsgno=stream->nmsgs; newmsgno > 0L; newmsgno--)
	      if((mc = mail_elt(stream, newmsgno)) && mc->searched)
		break;
	}
    }

    return(mn_raw2m(msgmap, newmsgno));
}
