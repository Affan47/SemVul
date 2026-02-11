printmessage(int Msg)
{
	L9BYTE* Msgptr=startmd;
	L9BYTE Data;

	int len;
	L9UINT16 Off;

	while (Msg>0 && Msgptr-endmd<=0)
	{
		Data=*Msgptr;
		if (Data&128)
		{
			Msgptr++;
			Msg-=Data&0x7f;
		}
		else {
			len=getmdlength(&Msgptr);
			Msgptr+=len;
		}
		Msg--;
	}
	if (Msg<0 || *Msgptr & 128) return;

	len=getmdlength(&Msgptr);
	if (len==0) return;

	while (len)
	{
		Data=*Msgptr++;
		len--;
		if (Data&128)
		{

			Off=(Data<<8) + *Msgptr++;
			len--;
		}
		else
		{
			Off=(wordtable[Data*2]<<8) + wordtable[Data*2+1];
		}
		if (Off==0x8f80) break;
		displaywordref(Off);
	}
}
