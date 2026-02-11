vmsg_infostr(const void *data, size_t size)
{
	static char msg[80];
	vendor_code_t vc;
	uint16 id;
	uint16 version;
	struct vmsg vmsg;

	if (size < sizeof vc)
		return "????";

	vc.u32 = gnutella_vendor_get_code(data);
	id = gnutella_vendor_get_selector_id(data);
	version = gnutella_vendor_get_version(data);

	if (!find_message(&vmsg, vc, id, version))
		str_bprintf(msg, sizeof msg , "%s/%uv%u",
			vendor_code_to_string(vc.u32), id, version);
	else
		str_bprintf(msg, sizeof msg, "%s/%uv%u '%s'",
			vendor_code_to_string(vc.u32), id, version, vmsg.name);

	return msg;
}
