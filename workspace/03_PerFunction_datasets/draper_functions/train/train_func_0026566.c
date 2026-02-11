detect_gfx_mode(void)
{
	if (L9GameType == L9_V3)
	{

		if (strstr(FirstLine,"price of magik") != 0)
			gfx_mode = GFX_V3A;
		else if (strstr(FirstLine,"the archers") != 0)
			gfx_mode = GFX_V3A;
		else if (strstr(FirstLine,"secret diary of adrian mole") != 0)
			gfx_mode = GFX_V3A;
		else if ((strstr(FirstLine,"worm in paradise") != 0)
			&& (strstr(FirstLine,"silicon dreams") == 0))
			gfx_mode = GFX_V3A;
		else if (strstr(FirstLine,"growing pains of adrian mole") != 0)
			gfx_mode = GFX_V3B;
		else if (strstr(FirstLine,"jewels of darkness") != 0 && picturesize < 11000)
			gfx_mode = GFX_V3B;
		else if (strstr(FirstLine,"silicon dreams") != 0)
		{
			if (picturesize > 11000
				|| (startdata[0] == 0x14 && startdata[1] == 0x7d)
				|| (startdata[0] == 0xd7 && startdata[1] == 0x7c))
				gfx_mode = GFX_V3C;
			else
				gfx_mode = GFX_V3B;
		}
		else
			gfx_mode = GFX_V3C;
	}
	else
		gfx_mode = GFX_V2;
}
