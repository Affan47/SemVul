getqword()
{
	if (codep-ocodep+8 <= maxlen) {
		uint64 w;
		w = uint64(codep[0])<< 0 | uint64(codep[1])<< 8 | uint64(codep[2])<<16 | uint64(codep[3])<<24
		  | uint64(codep[4])<<32 | uint64(codep[5])<<40 | uint64(codep[6])<<48 | uint64(codep[7])<<56;
		codep += 8;
		return w;
	} else {
		invalidate();
		return 0;
	}
}
