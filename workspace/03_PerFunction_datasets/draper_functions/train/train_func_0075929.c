log_spec(struct usnic_vnic_res_spec *res_spec)
{
	char buf[512];
	usnic_vnic_spec_dump(buf, sizeof(buf), res_spec);
	usnic_dbg("%s\n", buf);
}
