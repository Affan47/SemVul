freerdp_check_fds(freerdp* instance)
{
	rdpRdp* rdp;
	int status;

	rdp = (rdpRdp*) instance->rdp;

	status = rdp_check_fds(rdp);
	if (status < 0)
		return False;

	return True;
}
