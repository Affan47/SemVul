pipe_stop(struct r8a66597 *r8a66597, struct r8a66597_pipe *pipe)
{
	u16 tmp;

	tmp = r8a66597_read(r8a66597, pipe->pipectr) & PID;
	if ((tmp & PID_STALL11) != PID_STALL11)
		r8a66597_mdfy(r8a66597, PID_STALL, PID, pipe->pipectr);
	r8a66597_mdfy(r8a66597, PID_NAK, PID, pipe->pipectr);
	r8a66597_reg_wait(r8a66597, pipe->pipectr, PBUSY, 0);
}
