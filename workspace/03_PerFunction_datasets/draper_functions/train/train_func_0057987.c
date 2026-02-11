MergeMousePacket(int *relx, int *rely, int buttons)
{
	int mouse_inwrite;
	int distx, disty;


	if (intype != IKBD_PACKET_MOUSE)
		return;


	if (inread == inwrite)
		return;


	mouse_inwrite = (inwrite-3) & (inbufferlen-1);


	if ((inread == mouse_inwrite) ||
		(inread == ((mouse_inwrite+1) & (inbufferlen-1))) ||
		(inread == ((mouse_inwrite+2) & (inbufferlen-1))) )
		return;


	if ((inbuffer[mouse_inwrite]<=0xf8) && (inbuffer[mouse_inwrite]>=0xfb))
		return;


	if (inbuffer[mouse_inwrite] != (0xf8 | (buttons & 3)))
		return;


	distx = *relx + inbuffer[(mouse_inwrite+1) & (inbufferlen-1)];
	if (abs(distx) > MOUSE_DELTA_MAX)
		return;

	disty = *rely + inbuffer[(mouse_inwrite+2) & (inbufferlen-1)];
	if (abs(disty) > MOUSE_DELTA_MAX)
		return;


	inwrite = mouse_inwrite;
	*relx = distx;
	*rely = disty;
}
