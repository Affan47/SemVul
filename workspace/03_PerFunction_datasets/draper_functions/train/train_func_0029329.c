recvData(FILE* fdin, FILE* fdout)
{
    state |= S_TRANSFER;
    if (setjmp(urgcatch) != 0) {
	state &= ~S_TRANSFER;
	return (false);
    }
#define	PACK(a,b)	(((a)<<8)|(b))
    switch (PACK(type,mode)) {
    case PACK(TYPE_I,MODE_S):
    case PACK(TYPE_L,MODE_S):
	if (recvIData(fileno(fdin), fileno(fdout))) {
	    state &= ~S_TRANSFER;
	    return (true);
	}
	break;
    case PACK(TYPE_I,MODE_Z):
    case PACK(TYPE_L,MODE_Z):
	if (recvZData(fileno(fdin), fileno(fdout))) {
	    state &= ~S_TRANSFER;
	    return (true);
	}
	break;
    case PACK(TYPE_A,MODE_S):
	for (;;) {
	    int c = getc(fdin);
	    if (c == EOF) {
		fflush(fdout);
		if (ferror(fdin)) {
		    perror_reply(426, "Data Connection", errno);
		    break;
		}
		if (ferror(fdout)) {
		    perror_reply(452, "Error writing output file", errno);
		    break;
		}
		state &= ~S_TRANSFER;
		return (true);
	    }
	    byte_count++;
	    if (c == '\r') {
		if (ferror(fdout)) {
		    perror_reply(452, "Error writing output file", errno);
		    break;
		}
		c = getc(fdin);
		if (c != '\n') {
		    putc('\r', fdout);
		    if (c == EOF)
			continue;
		}
		byte_count++;
	    }
	    putc(c, fdout);
	}
	break;
    default:
	reply(550, "TYPE %s, MODE %s not implemented."
	    , typenames[type]
	    , modenames[mode]
	);
	break;
    }
#undef PACK
    state &= ~S_TRANSFER;
    return (false);
}
