bd_needed_req(struct bdc_req *req)
{
	int bd_needed = 0;
	int remaining;


	if (req->usb_req.length == 0)
		return 1;


	remaining = req->usb_req.length % BD_MAX_BUFF_SIZE;
	if (remaining)
		bd_needed++;


	remaining = req->usb_req.length / BD_MAX_BUFF_SIZE;
	bd_needed += remaining;

	return bd_needed;
}
