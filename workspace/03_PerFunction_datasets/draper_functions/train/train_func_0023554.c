mk_reply(int attr, void *data, int sz)
{
	char *s = data;
	int n, i, ret = 0;

	switch (attr) {
	case IB_PING_ATTR:
		break;
	case IB_HOSTINFO_ATTR:
		if (gethostname(s, sz) < 0)
			snprintf(s, sz, "?hostname?");
		s[sz - 1] = 0;
		if ((n = strlen(s)) >= sz - 1) {
			ret = sz;
			break;
		}
		s[n] = '.';
		s += n + 1;
		sz -= n + 1;
		ret += n + 1;
		if (getdomainname(s, sz) < 0)
			snprintf(s, sz, "?domainname?");
		if ((n = strlen(s)) == 0)
			s[-1] = 0;
		else
			ret += n;
		break;
	case IB_CPUINFO_ATTR:
		s[0] = '\0';
		for (i = 0; i < host_ncpu && sz > 0; i++) {
			n = snprintf(s, sz, "cpu %d: model %s MHZ %s\n",
				     i, cpus[i].model, cpus[i].mhz);
			if (n >= sz) {
				IBWARN("cpuinfo truncated");
				ret = sz;
				break;
			}
			sz -= n;
			s += n;
			ret += n;
		}
		ret++;
		break;
	default:
		DEBUG("unknown attr %d", attr);
	}
	return ret;
}
