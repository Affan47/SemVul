cli_scan_structured(cli_ctx *ctx)
{
	char buf[8192];
	int result = 0;
	unsigned int cc_count = 0;
	unsigned int ssn_count = 0;
	int done = 0;
	fmap_t *map;
	size_t pos = 0;
	int (*ccfunc)(const unsigned char *buffer, int length);
	int (*ssnfunc)(const unsigned char *buffer, int length);
	unsigned int viruses_found = 0;

    if(ctx == NULL)
	return CL_ENULLARG;

    map = *ctx->fmap;

    if(ctx->engine->min_cc_count == 1)
	ccfunc = dlp_has_cc;
    else
	ccfunc = dlp_get_cc_count;

    switch((ctx->options & CL_SCAN_STRUCTURED_SSN_NORMAL) | (ctx->options & CL_SCAN_STRUCTURED_SSN_STRIPPED)) {

	case (CL_SCAN_STRUCTURED_SSN_NORMAL | CL_SCAN_STRUCTURED_SSN_STRIPPED):
	    if(ctx->engine->min_ssn_count == 1)
		ssnfunc = dlp_has_ssn;
	    else
		ssnfunc = dlp_get_ssn_count;
	    break;

	case CL_SCAN_STRUCTURED_SSN_NORMAL:
	    if(ctx->engine->min_ssn_count == 1)
		ssnfunc = dlp_has_normal_ssn;
	    else
		ssnfunc = dlp_get_normal_ssn_count;
	    break;

	case CL_SCAN_STRUCTURED_SSN_STRIPPED:
	    if(ctx->engine->min_ssn_count == 1)
		ssnfunc = dlp_has_stripped_ssn;
	    else
		ssnfunc = dlp_get_stripped_ssn_count;
	    break;

	default:
	    ssnfunc = NULL;
    }

    while(!done && ((result = fmap_readn(map, buf, pos, 8191)) > 0)) {
	pos += result;
	if((cc_count += ccfunc((const unsigned char *)buf, result)) >= ctx->engine->min_cc_count)
	    done = 1;

	if(ssnfunc && ((ssn_count += ssnfunc((const unsigned char *)buf, result)) >= ctx->engine->min_ssn_count))
	    done = 1;
    }

    if(cc_count != 0 && cc_count >= ctx->engine->min_cc_count) {
	cli_dbgmsg("cli_scan_structured: %u credit card numbers detected\n", cc_count);
	cli_append_virus(ctx,"Heuristics.Structured.CreditCardNumber");
	if (SCAN_ALL)
	    viruses_found++;
	else
	    return CL_VIRUS;
    }

    if(ssn_count != 0 && ssn_count >= ctx->engine->min_ssn_count) {
	cli_dbgmsg("cli_scan_structured: %u social security numbers detected\n", ssn_count);
	cli_append_virus(ctx,"Heuristics.Structured.SSN");
	if (SCAN_ALL)
	    viruses_found++;
	else
	    return CL_VIRUS;
    }

    if (SCAN_ALL && viruses_found)
	return CL_VIRUS;
    return CL_CLEAN;
}
