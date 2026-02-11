adjust_clen(struct sip_msg* msg, int body_delta, int proto)
{
	struct lump* anchor;
	char* clen_buf;
	int clen_len;


	clen_buf = 0;
	anchor=0;


#ifdef USE_TCP
	if (proto == PROTO_TCP
#ifdef USE_TLS
	    || proto == PROTO_TLS
#endif
	    ) {
		if (parse_headers(msg, HDR_CONTENTLENGTH_F, 0)==-1){
			LM_ERR("parsing content-length\n");
			goto error;
		}
		if (msg->content_length==0){


			anchor=anchor_lump(msg, msg->unparsed-msg->buf, 0,
												HDR_CONTENTLENGTH_T);
			if (anchor==0){
				LM_ERR("cannot set clen anchor\n");
				goto error;
			}
		}
	}
#endif


	if ((anchor==0) && body_delta){
		if (parse_headers(msg, HDR_CONTENTLENGTH_F, 0) == -1) {
			LM_ERR("parsing Content-Length\n");
			goto error;
		}


		if ((msg->content_length==0)){


			if (proto!=PROTO_UDP){
				anchor=anchor_lump(msg, msg->unparsed-msg->buf, 0,
													HDR_CONTENTLENGTH_T);
				if (anchor==0){
					LM_ERR("cannot set clen anchor\n");
					goto error;
				}
			}else{
				LM_DBG("the UDP packet has no clen => not adding one \n");
			}
		}else{

			anchor = del_lump(	msg, msg->content_length->name.s - msg->buf,
								msg->content_length->len, HDR_CONTENTLENGTH_T);
			if (anchor==0) {
				LM_ERR("can't remove original Content-Length\n");
				goto error;
			}
		}
	}

	if (anchor){
		clen_buf = clen_builder(msg, &clen_len, body_delta);
		if (!clen_buf) goto error;
		if (insert_new_lump_after(anchor, clen_buf, clen_len,
					HDR_CONTENTLENGTH_T) == 0)
			goto error;
	}

	return 0;
error:
	if (clen_buf) pkg_free(clen_buf);
	return -1;
}
