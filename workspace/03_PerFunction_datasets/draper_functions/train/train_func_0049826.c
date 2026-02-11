method_name(ccp_options *opt,ccp_options *opt2)
{
    static char result[64];

    if (!ANY_COMPRESS(*opt))
       return "(none)";
    switch (opt->method) {
    case CI_DEFLATE:
       if (opt2 != NULL && opt2->deflate_size != opt->deflate_size)
           sprintf(result, "Deflate (%d/%d)", opt->deflate_size,
                   opt2->deflate_size);
       else
           sprintf(result, "Deflate (%d)", opt->deflate_size);
       break;
    case CI_BSD_COMPRESS:
       if (opt2 != NULL && opt2->bsd_bits != opt->bsd_bits)
           sprintf(result, "BSD-Compress (%d/%d)", opt->bsd_bits,
                   opt2->bsd_bits);
       else
           sprintf(result, "BSD-Compress (%d)", opt->bsd_bits);
       break;
    case CI_PREDICTOR_1:
       return "Predictor 1";
    case CI_PREDICTOR_2:
       return "Predictor 2";
    case CI_LZS_COMPRESS:
	if (opt2 != NULL && (opt2->lzs_hists != opt->lzs_hists ||
	    opt2->lzs_cmode != opt->lzs_cmode))
	    sprintf(result, "LZS (hists %d check %d/hists %d check %d)",
		    opt->lzs_hists, opt->lzs_cmode,
		    opt2->lzs_hists, opt2->lzs_cmode);
	else
	    sprintf(result, "LZS (hists %d check %d)",
		    opt->lzs_hists, opt->lzs_cmode);
	break;
    default:
       sprintf(result, "Method %d", opt->method);
    }
    return result;
}
