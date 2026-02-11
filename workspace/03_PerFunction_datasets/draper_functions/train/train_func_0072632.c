OPL3_STATUS_RESET(OPL3 *chip,int flag)
{

	chip->status &= ~flag;
	if(chip->status & 0x80)
	{
		if (!(chip->status & 0x7f))
		{
			chip->status &= 0x7f;

			if(chip->IRQHandler) (chip->IRQHandler)(chip->IRQParam,0);
		}
	}
}
