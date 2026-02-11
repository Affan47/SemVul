write_radattr(struct pppd_compat_pd *pd, struct rad_packet_t *pack)
{
	struct ap_session *ses = pd->ses;
	struct rad_attr_t *attr;
	struct rad_dict_value_t *val;
	FILE *f;
	char *fname1, *fname2 = NULL;
	int i;
	in_addr_t addr;

	fname1 = _malloc(PATH_MAX);
	if (!fname1) {
		log_emerg("pppd_compat: out of memory\n");
		return;
	}

	if (ses->state == AP_STATE_ACTIVE) {
		fname2 = _malloc(PATH_MAX);
		if (!fname2) {
			log_emerg("pppd_compat: out of memory\n");
			_free(fname1);
			return;
		}
	}

	if (ses->state == AP_STATE_ACTIVE) {
		sprintf(fname1, "%s.%s", conf_radattr_prefix, ses->ifname);
		sprintf(fname2, "%s_old.%s", conf_radattr_prefix, ses->ifname);
		if (rename(fname1, fname2)) {
			log_ppp_warn("pppd_compat: rename: %s\n", strerror(errno));
		}
	} else {
		sprintf(fname1, "%s.XXXXXX", conf_radattr_prefix);
		mktemp(fname1);
	}

	f = fopen(fname1, "w");
	if (f) {
		list_for_each_entry(attr, &pack->attrs, entry) {
			fprintf(f, "%s ", attr->attr->name);
			switch (attr->attr->type) {
				case ATTR_TYPE_INTEGER:
					val = rad_dict_find_val(attr->attr, attr->val);
					if (val)
						fprintf(f, "%s\n", val->name);
					else
						fprintf(f, "%i\n", attr->val.integer);
					break;
				case ATTR_TYPE_STRING:
					fprintf(f, "%s\n", attr->val.string);
					break;
				case ATTR_TYPE_OCTETS:
					for (i = 0; i < attr->len; i++)
						fprintf(f, "%02X", attr->val.octets[i]);
					fprintf(f, "\n");
					break;
				case ATTR_TYPE_IPADDR:
					addr = ntohl(attr->val.ipaddr);
					fprintf(f, "%i.%i.%i.%i\n", (addr >> 24) & 0xff, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff);
					break;
				case ATTR_TYPE_DATE:
					fprintf(f, "%lu\n", attr->val.date);
					break;
			}
		}
		fclose(f);
	} else
		log_ppp_warn("pppd_compat: failed to create '%s': %s\n", fname1, strerror(errno));

	if (ses->state == AP_STATE_ACTIVE) {
		_free(fname1);
		_free(fname2);
	} else
		pd->tmp_fname = fname1;
}
