pia_set_input_cb1(int which, int data)
{
	struct pia6821 *p = pia + which;


	data = data ? 1 : 0;


	if (p->in_cb1 ^ data)
	{

		if ((data && C1_LOW_TO_HIGH(p->ctl_b)) || (!data && C1_HIGH_TO_LOW(p->ctl_b)))
		{

			p->irq_b1 = 1;


			update_6821_interrupts(p);


			if (C2_OUTPUT(p->ctl_b) && C2_STROBE_MODE(p->ctl_b) && STROBE_C1_RESET(p->ctl_b))
			{

				if (!p->irq_b1)
				{

					if (!p->out_cb2)
						if (p->intf->out_cb2_func) p->intf->out_cb2_func(0, 1);


					p->out_cb2 = 1;
				}
			}
		}
	}


	p->in_cb1 = data;
	p->in_set |= PIA_IN_SET_CB1;
}
