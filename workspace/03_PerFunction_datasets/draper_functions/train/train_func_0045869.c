set_pwm(byte osc, float ds, byte resol)
	{

	byte res[1];
	u16 ocxrs, ocx;

	if( (ds > 100) || (resol < 6) || (resol > 16) )
		return INVARG;
	ocxrs = pow(2.0, resol);
	ocx = (u16)(0.01 * ds * ocxrs + 0.5);
	if(osc == 0)
		sendByte(SETPWM1);
	else
		sendByte(SETPWM2);
	sendInt(ocxrs-1);
	sendInt(ocx);
	*res = COMERR;
	sread(1, res);
	if(*res != 'D')
		{
		fprintf(stderr, "SETPWM error\n");
		return *res;
		}
	return 0;
	}
