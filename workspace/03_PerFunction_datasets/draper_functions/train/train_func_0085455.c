get_state(byte pin, byte *st)
	{

	byte res[1];

	sendByte(GETSTATE);
	sendByte(pin);
	*res = COMERR;
	sread(1, res);
	if(*res != 'D')
		{
		fprintf(stderr,"GETSTATE error\n");
		return *res;
		}
	if(sread(1,res) != 1) return COMERR;
	*st = *res;
	return 0;
	}
