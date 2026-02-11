stv_vdp2_dynamic_res_change()
{
	static UINT16 horz,vert;

	switch( STV_VDP2_VRES & 3 )
	{
		case 0: vert = 224; break;
		case 1: vert = 240; break;
		case 2: vert = 256; break;
		case 3:
			logerror("WARNING: V Res setting (3) not allowed!\n");
			vert = 256;
			break;
	}


	if((STV_VDP2_LSMD & 3) == 3) { vert*=2;  }

	switch( STV_VDP2_HRES & 7 )
	{
		case 0: horz = 320; break;
		case 1: horz = 352; break;
		case 2: horz = 640; break;
		case 3: horz = 704; break;


		case 4: horz = 320; vert = 480; break;
		case 5: horz = 352; vert = 480; break;
		case 6: horz = 640; vert = 480; break;
		case 7: horz = 704; vert = 480; break;
	}

	set_visible_area(0*8, horz-1,0*8, vert-1);
}
