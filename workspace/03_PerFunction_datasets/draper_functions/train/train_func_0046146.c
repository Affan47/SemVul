insert16(short unsigned int x)
{
	if (asmflags & F_LOHI)
	{	insert8(x);
		insert8(x>>8);
	}
	else
	{	insert8(x>>8);
		insert8(x);
	}
}
