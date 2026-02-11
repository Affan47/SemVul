drbd_nla_parse_nested(struct nlattr *tb[], int maxtype, struct nlattr *nla,
			  const struct nla_policy *policy)
{
	int err;

	err = drbd_nla_check_mandatory(maxtype, nla);
	if (!err)
		err = nla_parse_nested(tb, maxtype, nla, policy);

	return err;
}
