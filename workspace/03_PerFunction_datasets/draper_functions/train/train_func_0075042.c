hd_end_request(int err, unsigned int bytes)
{
	if (__blk_end_request(hd_req, err, bytes))
		return true;
	hd_req = NULL;
	return false;
}
