SCSP_TimersAddTicks(int ticks)
{
	if(TimCnt[0]<=0xff00)
	{
 		TimCnt[0] += ticks << (8-((SCSPs[0].udata.data[0x18/2]>>8)&0x7));
		if (TimCnt[0] > 0xFF00)
		{
			TimCnt[0] = 0xFFFF;
			SCSPs[0].udata.data[0x20/2]|=0x40;
		}
		SCSPs[0].udata.data[0x18/2]&=0xff00;
		SCSPs[0].udata.data[0x18/2]|=TimCnt[0]>>8;
	}

	if(TimCnt[1]<=0xff00)
	{
		TimCnt[1] += ticks << (8-((SCSPs[0].udata.data[0x1a/2]>>8)&0x7));
		if (TimCnt[1] > 0xFF00)
		{
			TimCnt[1] = 0xFFFF;
			SCSPs[0].udata.data[0x20/2]|=0x80;
		}
		SCSPs[0].udata.data[0x1a/2]&=0xff00;
		SCSPs[0].udata.data[0x1a/2]|=TimCnt[1]>>8;
	}

	if(TimCnt[2]<=0xff00)
	{
		TimCnt[2] += ticks << (8-((SCSPs[0].udata.data[0x1c/2]>>8)&0x7));
		if (TimCnt[2] > 0xFF00)
		{
			TimCnt[2] = 0xFFFF;
			SCSPs[0].udata.data[0x20/2]|=0x100;
		}
		SCSPs[0].udata.data[0x1c/2]&=0xff00;
		SCSPs[0].udata.data[0x1c/2]|=TimCnt[2]>>8;
	}
}
