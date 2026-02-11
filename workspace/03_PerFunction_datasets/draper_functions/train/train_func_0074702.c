getdword()
{
	if (codep-ocodep+4<=maxlen) {
		uint32 w;
		addr += 4;
		w = codep[3] | (codep[2]<<8) | (codep[1]<<16) | (codep[0]<<24);
		codep += 4;
		return w;
	} else {
		invalidate();
		return 0;
	}
}
