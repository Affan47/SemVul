build_sequence(MAILSTREAM *stream, MSGNO_S *msgmap, long int *count)
{
#define	SEQ_INCREMENT	128
    long    n = 0L, i, x, lastn = 0L, runstart = 0L;
    size_t  size = SEQ_INCREMENT;
    char   *seq = NULL, *p;
    MESSAGECACHE *mc;

    if(!stream)
      return(NULL);

    if(count){
	if(*count > 0L)
	  size = MAX(size, MIN((*count) * 4, 16384));

	*count = 0L;
    }

    for(x = 1L; x <= stream->nmsgs; x++){
	if(msgmap){
	    if((i = mn_m2raw(msgmap, x)) == 0L)
	      continue;
	}
	else
	  i = x;

	if(i > 0L && i <= stream->nmsgs
	   && (mc = mail_elt(stream, i)) && mc->sequence){
	    n++;
	    if(!seq)
	      seq = p = fs_get(size);


	    if(lastn){
		if(lastn + 1L == i){
		    lastn = i;
		    continue;
		}
		else if(runstart != lastn){
		    *p++ = (runstart + 1L == lastn) ? ',' : ':';
		    sstrncpy(&p, long2string(lastn), size-(p-seq));
		}
	    }

	    runstart = lastn = i;

	    if(n > 1L && (p-seq) < size)
	      *p++ = ',';

	    if(size - (p - seq) < 16){
		size_t offset = p - seq;
		size += SEQ_INCREMENT;
		fs_resize((void **)&seq, size);
		p = seq + offset;
	    }

	    sstrncpy(&p, long2string(i), size-(p-seq));
	}
    }

    if(lastn && runstart != lastn){
	if((p-seq) < size)
	  *p++ = (runstart + 1L == lastn) ? ',' : ':';

	sstrncpy(&p, long2string(lastn), size-(p-seq));
    }

    if(seq && (p-seq) < size)
      *p  = '\0';

    if(seq)
      seq[size-1] = '\0';

    if(count)
      *count = n;

    return(seq);
}
