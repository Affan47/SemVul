cwrite_ts(uint8_t *buf, ts_packet *p, long length){
	long count,i;
	uint8_t sync,dummy;

	sync = 0x47;
	memcpy(buf,&sync,1);
	count = 1;
	memcpy(buf+count,p->pid,2);
	count += 2;
	memcpy(buf+count,&p->flags,1);
	count++;


	if (! (p->flags & ADAPT_FIELD) && (p->flags & PAYLOAD)){
		memcpy(buf+count,p->data,184);
		count += 184;
	} else {
		memcpy(buf+count,&p->adapt_length,1);
		count++;
		memcpy(buf+count,&p->adapt_flags,1);
		count++;

		if ( p->adapt_flags & PCR_FLAG ){
			memcpy(buf+count, p->pcr,6);
			count += 6;
		}
		if ( p->adapt_flags & OPCR_FLAG ){
			memcpy(buf+count, p->opcr,6);
			count += 6;
		}
		if ( p->adapt_flags & SPLICE_FLAG ){
			memcpy(buf+count, &p->splice_count,1);
			count++;
		}
		if( p->adapt_flags & TRANS_PRIV){
			memcpy(buf+count,&p->priv_dat_len,1);
			count++;
			memcpy(buf+count,p->priv_dat,p->priv_dat_len);
			count += p->priv_dat_len;
		}

		if( p->adapt_flags & ADAP_EXT_FLAG){
			memcpy(buf+count,&p->adapt_ext_len,1);
			count++;
			memcpy(buf+count,&p->adapt_eflags,1);
			count++;

			if( p->adapt_eflags & LTW_FLAG){
				memcpy(buf+count,p->ltw,2);
				count += 2;
			}
			if( p->adapt_eflags & PIECE_RATE){
				memcpy(buf+count,p->piece_rate,3);
				count += 3;
			}
			if( p->adapt_eflags & SEAM_SPLICE){
				memcpy(buf+count,p->dts,5);
				count += 5;
			}
		}
		dummy = 0xFF;
		for(i=0; i < p->stuffing ; i++){
			memcpy(buf+count,&dummy,1);
			count++;
		}
		if (p->flags & PAYLOAD){
			memcpy(buf+count,p->data,p->rest);
			count += p->rest;
		}
	}


	return count;
}
