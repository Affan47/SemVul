perl_store_vps(VALUE_PAIR *vp, HV *rad_hv)
{
        VALUE_PAIR	*nvp, *vpa, *vpn;
	AV		*av;
	char		namebuf[256], *name;
	char            buffer[1024];
	int		attr, len;

	hv_undef(rad_hv);
	nvp = paircopy(vp);

	while (nvp != NULL) {
		name = nvp->name;
		attr = nvp->attribute;
		vpa = paircopy2(nvp,attr);

		if (vpa->next) {
			av = newAV();
			vpn = vpa;
			while (vpn) {
				len = vp_prints_value(buffer, sizeof(buffer),
						vpn, FALSE);
				av_push(av, newSVpv(buffer, len));
				vpn = vpn->next;
			}
			hv_store(rad_hv, nvp->name, strlen(nvp->name),
					newRV_noinc((SV *) av), 0);
		} else {
			if ((vpa->flags.has_tag) &&
			    (vpa->flags.tag != 0)) {
				snprintf(namebuf, sizeof(namebuf), "%s:%d",
					 nvp->name, nvp->flags.tag);
				name = namebuf;
			}

			len = vp_prints_value(buffer, sizeof(buffer),
					      vpa, FALSE);
			hv_store(rad_hv, name, strlen(name),
				 newSVpv(buffer, len), 0);
		}

		pairfree(&vpa);
		vpa = nvp; while ((vpa != NULL) && (vpa->attribute == attr))
			vpa = vpa->next;
		pairdelete(&nvp, attr);
		nvp = vpa;
	}
}
