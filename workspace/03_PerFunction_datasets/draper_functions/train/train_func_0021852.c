emitqword(uint64 q)
{
	if (bigendian) {
		code.data[code.size+7] = (byte)q;
		code.data[code.size+6] = (byte)(q>>8);
		code.data[code.size+5] = (byte)(q>>16);
		code.data[code.size+4] = (byte)(q>>24);
		code.data[code.size+3] = (byte)(q>>32);
		code.data[code.size+2] = (byte)(q>>40);
		code.data[code.size+1] = (byte)(q>>48);
		code.data[code.size+0] = (byte)(q>>56);
	} else {
		code.data[code.size+0] = (byte)q;
		code.data[code.size+1] = (byte)(q>>8);
		code.data[code.size+2] = (byte)(q>>16);
		code.data[code.size+3] = (byte)(q>>24);
		code.data[code.size+4] = (byte)(q>>32);
		code.data[code.size+5] = (byte)(q>>40);
		code.data[code.size+6] = (byte)(q>>48);
		code.data[code.size+7] = (byte)(q>>56);
	}
	code.size += 8;
}
