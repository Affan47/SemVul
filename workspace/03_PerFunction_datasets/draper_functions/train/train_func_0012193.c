find_ecrec(vfile *vf, long searchlen, struct ecrec *ecrec)
{
    int res;
    avoff_t bufstart;
    int pos;
    char buf[BUFSIZE+3];
    avoff_t sres;
    int found;

    sres = av_lseek(vf, 0, AVSEEK_END);
    if(sres < 0)
        return sres;
    if(sres < ECREC_SIZE) {
        av_log(AVLOG_ERROR, "UZIP: Broken archive");
        return -EIO;
    }

    pos = 0;
    bufstart = sres - (ECREC_SIZE - 4);
    buf[0] = buf[1] = buf[2] = 0;
    found = 0;

    for(;searchlen && (bufstart || pos); searchlen--) {
	if(!pos) {
	    pos = BUFSIZE;
	    if(bufstart < pos) pos = bufstart;
	    bufstart -= pos;
	    buf[pos]   = buf[0];
	    buf[pos+1] = buf[1];
	    buf[pos+2] = buf[2];
            res = av_pread_all(vf, buf, pos, bufstart);
            if(res < 0)
                return res;
	}
	pos--;
	if(buf[pos] == 'P' && buf[pos+1] == 'K' &&
	   buf[pos+2] == 5 && buf[pos+3] == 6) {
	    found = 1;
	    break;
	}
    }

    if(!found) {
        av_log(AVLOG_ERROR,
               "UZIP: Couldn't find End of Central Directory Record");
        return -EIO;
    }

    bufstart += pos;
    res = av_pread_all(vf, buf, ECREC_SIZE, bufstart);
    if(res < 0)
        return res;

    ecrec->this_disk =     DBYTE(buf+ECREC_THIS_DISK);
    ecrec->cdir_disk =     DBYTE(buf+ECREC_CDIR_DISK);
    ecrec->this_entries =  DBYTE(buf+ECREC_THIS_ENTRIES);
    ecrec->total_entries = DBYTE(buf+ECREC_TOTAL_ENTRIES);
    ecrec->cdir_size =     QBYTE(buf+ECREC_CDIR_SIZE);
    ecrec->cdir_off =      QBYTE(buf+ECREC_CDIR_OFF);
    ecrec->comment_len =   DBYTE(buf+ECREC_COMMENT_LEN);

    return bufstart;
}
