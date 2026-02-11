drbd_nla_check_mandatory(int maxtype, struct nlattr *nla)
{
	struct nlattr *head = nla_data(nla);
	int len = nla_len(nla);
	int rem;


	nla_for_each_attr(nla, head, len, rem) {
		if (nla->nla_type & DRBD_GENLA_F_MANDATORY) {
			nla->nla_type &= ~DRBD_GENLA_F_MANDATORY;
			if (nla_type(nla) > maxtype)
				return -EOPNOTSUPP;
		}
	}
	return 0;
}
