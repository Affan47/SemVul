psx_hw_runcounters(void)
{
	int i;


	if (!intr_susp)
	{
		if (dma4_delay)
		{
			dma4_delay--;

			if (dma4_delay == 0)
			{
				SPU2interruptDMA4();

				if (dma4_cb)
				{
					call_irq_routine(dma4_cb, dma4_flag);
				}
			}
		}

		if (dma7_delay)
		{
			dma7_delay--;

			if (dma7_delay == 0)
			{
				SPU2interruptDMA7();

				if (dma7_cb)
				{
					call_irq_routine(dma7_cb, dma7_flag);
				}
			}
		}

		for (i = 0; i < iNumThreads; i++)
		{
			if (threads[i].iState == TS_WAITDELAY)
			{
				if (threads[i].waitparm > CLOCK_DIV)
				{
					threads[i].waitparm -= CLOCK_DIV;
				}
				else
				{
					threads[i].waitparm = 0;
					threads[i].iState = TS_READY;

					timerexp = 1;

					ps2_reschedule();
				}
			}
		}

		sys_time += 836;

		if (iNumTimers > 0)
		{
			for (i = 0; i < iNumTimers; i++)
			{
				if (iop_timers[i].iActive > 0)
				{
					iop_timers[i].count += 836;
					if (iop_timers[i].count >= iop_timers[i].target)
					{
						iop_timers[i].count -= iop_timers[i].target;


						call_irq_routine(iop_timers[i].handler, iop_timers[i].hparam);

						timerexp = 1;
					}
				}
			}
		}
	}


	for (i = 0; i < 4; i++)
	{
		if ((!(root_cnts[i].mode & RC_EN)) && (root_cnts[i].mode != 0))
		{
			if (root_cnts[i].mode & RC_DIV8)
			{
				root_cnts[i].count += 768/8;
			}
			else
			{
				root_cnts[i].count += 768;
			}

			if (root_cnts[i].count >= root_cnts[i].target)
			{
				if (!(root_cnts[i].mode & RC_RESET))
				{
					root_cnts[i].mode |= RC_EN;
				}
				else
				{
					root_cnts[i].count %= root_cnts[i].target;
				}

				psx_irq_set(1<<(4+i));
			}
		}
	}
}
