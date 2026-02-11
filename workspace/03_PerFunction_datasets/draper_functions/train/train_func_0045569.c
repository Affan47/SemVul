ccp_rejci(fsm *f,u_char *p,int len)
{
    ccp_options *go;
    ccp_options try;
    int unit;

    if(f->protocol == PPP_CCP)
      unit = lns[f->unit].ccp_unit;
    else
      unit = lns[f->unit].ccp_l_unit;

    go = &ccp_gotoptions[unit];

    try = *go;


    if (len == 0 && all_rejected[unit])
	return -1;

    if (go->deflate && len >= CILEN_DEFLATE
	&& p[0] == CI_DEFLATE && p[1] == CILEN_DEFLATE) {
	if (p[2] != DEFLATE_MAKE_OPT(go->deflate_size)
	    || p[3] != DEFLATE_CHK_SEQUENCE)
	    return 0;
	try.deflate = 0;
	p += CILEN_DEFLATE;
	len -= CILEN_DEFLATE;
    }
    if (go->bsd_compress && len >= CILEN_BSD_COMPRESS
	&& p[0] == CI_BSD_COMPRESS && p[1] == CILEN_BSD_COMPRESS) {
	if (p[2] != BSD_MAKE_OPT(BSD_CURRENT_VERSION, go->bsd_bits))
	    return 0;
	try.bsd_compress = 0;
	p += CILEN_BSD_COMPRESS;
	len -= CILEN_BSD_COMPRESS;
    }
    if (go->predictor_1 && len >= CILEN_PREDICTOR_1
	&& p[0] == CI_PREDICTOR_1 && p[1] == CILEN_PREDICTOR_1) {
	try.predictor_1 = 0;
	p += CILEN_PREDICTOR_1;
	len -= CILEN_PREDICTOR_1;
    }
    if (go->predictor_2 && len >= CILEN_PREDICTOR_2
	&& p[0] == CI_PREDICTOR_2 && p[1] == CILEN_PREDICTOR_2) {
	try.predictor_2 = 0;
	p += CILEN_PREDICTOR_2;
	len -= CILEN_PREDICTOR_2;
    }
    if(go->lzs && len >= CILEN_LZS_COMPRESS
       && p[0] == CI_LZS_COMPRESS && p[1] == CILEN_LZS_COMPRESS) {
	if(LZS_HIST_WORD(p[2], p[3]) != go->lzs_hists || p[4] != go->lzs_cmode)
	    return 0;
	try.lzs = 0;
	p += CILEN_LZS_COMPRESS;
	len -= CILEN_LZS_COMPRESS;
    }

    if (len != 0)
	return 0;

    if (f->state != OPENED)
	*go = try;

    return 1;
}
