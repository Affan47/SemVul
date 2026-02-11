i8x41_set_irq_line(int irqline, int state)
{
	switch( irqline )
	{
	case I8X41_INT_IBF:
		if (state != CLEAR_LINE)
		{
			STATE |= IBF;
			if (ENABLE & IBFI)
			{
				CONTROL |= IBFI_PEND;
			}
		}
		else
		{
			STATE &= ~IBF;
		}
		break;

	case I8X41_INT_TEST1:
		if( state != CLEAR_LINE )
		{
			CONTROL |= TEST1;
		}
		else
		{

			if( CONTROL & TEST1 )
			{

				if( ENABLE & CNT )
				{
					TIMER++;
					if( TIMER == 0 )
					{
						CONTROL |= TOVF;
						CONTROL |= TIRQ_PEND;
					}
				}
			}
			CONTROL &= ~TEST1;
		}
		break;
	}
}
