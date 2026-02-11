r8a66597_start_xclock(struct r8a66597 *r8a66597)
{
	u16 tmp;

	if (!r8a66597->pdata->on_chip) {
		tmp = r8a66597_read(r8a66597, SYSCFG0);
		if (!(tmp & XCKE))
			r8a66597_bset(r8a66597, XCKE, SYSCFG0);
	}
}
