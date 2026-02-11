head_check(unsigned long head)
{
	if
	(

		((head & 0xffe00000) != 0xffe00000)
		||

		(!((head>>17)&3))
		||

		(((head>>12)&0xf) == 0xf)
		||

		(((head>>10)&0x3) == 0x3 )

	)
	{
		return FALSE;
	}

	else
	{
		return TRUE;
	}
}
