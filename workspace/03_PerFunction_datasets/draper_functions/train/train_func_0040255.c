VSL_NextLog(const struct VSM_data *vd, uint32_t **pp, uint64_t *bits)
{
	struct vsl *vsl;
	uint32_t *p;
	unsigned char t;
	unsigned u;
	int i;

	CHECK_OBJ_NOTNULL(vd, VSM_MAGIC);
	vsl = vd->vsl;
	CHECK_OBJ_NOTNULL(vsl, VSL_MAGIC);

	while (1) {
		i = vsl_nextlog(vsl, &p);
		if (i != 1)
			return (i);
		u = VSL_ID(p);
		t = VSL_TAG(p);
		switch(t) {
		case SLT_SessionOpen:
		case SLT_ReqStart:
			vbit_set(vsl->vbm_client, u);
			vbit_clr(vsl->vbm_backend, u);
			break;
		case SLT_BackendOpen:
		case SLT_BackendXID:
			vbit_clr(vsl->vbm_client, u);
			vbit_set(vsl->vbm_backend, u);
			break;
		default:
			break;
		}
		if (vsl->skip) {
			--vsl->skip;
			continue;
		} else if (vsl->keep) {
			if (--vsl->keep == 0)
				return (-1);
		}

		if (vbit_test(vsl->vbm_select, t)) {
			*pp = p;
			return (1);
		}
		if (vbit_test(vsl->vbm_supress, t))
			continue;
		if (vsl->b_opt && !vbit_test(vsl->vbm_backend, u))
			continue;
		if (vsl->c_opt && !vbit_test(vsl->vbm_client, u))
			continue;
		if (vsl->regincl != NULL) {
			i = VRE_exec(vsl->regincl, VSL_DATA(p), VSL_LEN(p),
			    0, 0, NULL, 0);
			if (i == VRE_ERROR_NOMATCH)
				continue;
		}
		if (vsl->regexcl != NULL) {
			i = VRE_exec(vsl->regexcl, VSL_DATA(p), VSL_LEN(p),
			    0, 0, NULL, 0);
			if (i != VRE_ERROR_NOMATCH)
				continue;
		}
		if (bits != NULL) {
			struct vsl_re_match *vrm;
			int j = 0;
			VTAILQ_FOREACH(vrm, &vsl->matchers, next) {
				if (vrm->tag == t) {
					i = VRE_exec(vrm->re, VSL_DATA(p),
						     VSL_LEN(p), 0, 0, NULL, 0);
					if (i >= 0)
						*bits |= (uintmax_t)1 << j;
				}
				j++;
			}
		}
		*pp = p;
		return (1);
	}
}
