usbhsp_pipe_buf_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
	if (usbhs_pipe_is_dcp(pipe))
		return;

	__usbhsp_pipe_xxx_set(pipe, 0, PIPEBUF, mask, val);
}
