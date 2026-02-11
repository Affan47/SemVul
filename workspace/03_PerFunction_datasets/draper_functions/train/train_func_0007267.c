Con_Print (const char *txt)
{
	int		y, c, l;
	static qboolean	cr = false;
	int		mask, color;
	qboolean colors = false;

	if (!con.initialized)
		return;

	color = COLOR_WHITE;
	mask = 0;

	switch (*txt) {
	case 1:
	case 2:
		mask = 128;
		txt++;
		break;
	case COLOR_ONE:
		txt++;
		if(Q_IsColorString( txt )) {
			color = ColorIndex(*(txt+1));
			txt+=2;
		}
		break;
	case COLOR_ENABLE:
		txt++;
		colors = true;
		break;
	}

	while ( (c = *txt) != 0 )
	{
		if ( colors && Q_IsColorString( txt ) ) {
			color = ColorIndex( *(txt+1) );
			txt += 2;
			continue;
		}

		if (con.x) {

			for (l=0 ; l< con.linewidth ; l++) {
				if ( txt[l] <= ' ')
					break;
			}


			if (l != con.linewidth && (con.x + l > con.linewidth) )
				Con_Linefeed();
		}
		else {
			if (cr) {
				con.current--;
				cr = false;
			}
			Con_Linefeed();
		}

		switch (c)
		{
		case '\r':
			cr = true;
		case '\n':
			color = COLOR_WHITE;
			con.x = 0;
			break;
		default:
			y = con.current % con.totallines;
			con.text[y*con.linewidth+con.x] = c | mask | (color << 8);
			con.x++;
			if (con.x >= con.linewidth)
				con.x = 0;

			break;
		}
		txt++;
	}
}
