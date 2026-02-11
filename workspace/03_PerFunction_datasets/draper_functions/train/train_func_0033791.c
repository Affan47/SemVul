chan_calc(unsigned int chan)
{
	YM2151Operator *op;
	unsigned int env;
	UINT32 AM = 0;

	m2 = c1 = c2 = mem = 0;
	op = &PSG->oper[chan*4];

	*op->mem_connect = op->mem_value;

	if (op->ams)
		AM = PSG->lfa << (op->ams-1);
	env = volume_calc(op);
	{
		INT32 out = op->fb_out_prev + op->fb_out_curr;
		op->fb_out_prev = op->fb_out_curr;

		if (!op->connect)

			mem = c1 = c2 = op->fb_out_prev;
		else

			*op->connect = op->fb_out_prev;

		op->fb_out_curr = 0;
		if (env < ENV_QUIET)
		{
			if (!op->fb_shift)
				out=0;
			op->fb_out_curr = op_calc1(op, env, (out<<op->fb_shift) );
		}
	}

	env = volume_calc(op+1);
	if (env < ENV_QUIET)
		*(op+1)->connect += op_calc(op+1, env, m2);

	env = volume_calc(op+2);
	if (env < ENV_QUIET)
		*(op+2)->connect += op_calc(op+2, env, c1);

	env = volume_calc(op+3);
	if (env < ENV_QUIET)
		chanout[chan]    += op_calc(op+3, env, c2);


	op->mem_value = mem;
}
