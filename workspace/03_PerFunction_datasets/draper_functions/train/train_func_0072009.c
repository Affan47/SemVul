RFC2616_Ttl(const struct sess *sp)
{
	unsigned max_age, age;
	double h_date, h_expires;
	char *p;
	const struct http *hp;
	struct exp *expp;

	expp = &sp->wrk->busyobj->exp;

	hp = sp->wrk->busyobj->beresp;

	assert(expp->entered != 0.0 && !isnan(expp->entered));

	expp->ttl = cache_param->default_ttl;

	max_age = age = 0;
	h_expires = 0;
	h_date = 0;


	if (http_GetHdr(hp, H_Age, &p)) {
		age = strtoul(p, NULL, 0);
		expp->age = age;
	}
	if (http_GetHdr(hp, H_Expires, &p))
		h_expires = VTIM_parse(p);

	if (http_GetHdr(hp, H_Date, &p))
		h_date = VTIM_parse(p);

	switch (sp->req->err_code) {
	default:
		expp->ttl = -1.;
		break;
	case 200:
	case 203:
	case 300:
	case 301:
	case 302:
	case 307:
	case 410:
	case 404:


		if ((http_GetHdrField(hp, H_Cache_Control, "s-maxage", &p) ||
		    http_GetHdrField(hp, H_Cache_Control, "max-age", &p)) &&
		    p != NULL) {

			if (*p == '-')
				max_age = 0;
			else
				max_age = strtoul(p, NULL, 0);

			if (age > max_age)
				expp->ttl = 0;
			else
				expp->ttl = max_age - age;
			break;
		}


		if (h_expires == 0)
			break;


		if (h_expires < h_date) {
			expp->ttl = 0;
			break;
		}

		if (h_date == 0 ||
		    fabs(h_date - expp->entered) < cache_param->clock_skew) {


			if (h_expires < expp->entered)
				expp->ttl = 0;
			else
				expp->ttl = h_expires -
				    expp->entered;
			break;
		} else {


			expp->ttl = (int)(h_expires - h_date);
		}

	}


	WSP(sp, SLT_TTL,
	    "%u RFC %.0f %.0f %.0f %.0f %.0f %.0f %.0f %u",
	    sp->req->xid, expp->ttl, -1., -1., expp->entered,
	    expp->age, h_date, h_expires, max_age);
}
