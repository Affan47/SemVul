iscsid_req_by_sid(iscsiadm_cmd_e cmd, int sid)
{
	int err, fd;

	err = iscsid_req_by_sid_async(cmd, sid, &fd);
	if (err)
		return err;
	return iscsid_req_wait(cmd, fd);
}
