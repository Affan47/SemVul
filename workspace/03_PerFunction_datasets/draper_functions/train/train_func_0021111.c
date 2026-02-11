pia_set_input_ca1(int which, int data)
{
	struct pia6821 *p = pia + which;


	data = data ? 1 : 0;


	if (p->in_ca1 ^ data)
	{

		if ((data && C1_LOW_TO_HIGH(p->ctl_a)) || (!data && C1_HIGH_TO_LOW(p->ctl_a)))
		{

			p->irq_a1 = 1;


			update_6821_interrupts(p);


			if (C2_OUTPUT(p->ctl_a) && C2_STROBE_MODE(p->ctl_a) && STROBE_C1_RESET(p->ctl_a))
			{

				if (!p->out_ca2)
					if (p->intf->out_ca2_func) p->intf->out_ca2_func(0, 1);


				p->out_ca2 = 1;
			}
		}
	}


	p->in_ca1 = data;
	p->in_set |= PIA_IN_SET_CA1;
}
