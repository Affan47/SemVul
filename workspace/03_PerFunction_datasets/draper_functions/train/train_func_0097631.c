parse_oid(const char *str, const heim_oid *def, heim_oid *oid)
{
    int ret;
    if (str)
	ret = der_parse_heim_oid (str, " .", oid);
    else
	ret = der_copy_oid(def, oid);
    if  (ret)
	errx(1, "parse_oid failed for: %s", str ? str : "default oid");
}
