listentry( int num )
{
	static char	buf[600];
	char		*name, tracknum[20];
	int		digits;
	int		sdigits;

	if (num >= 0 && num < cur_ntracks)
	{


		digits = 2;
		sdigits = cur_nsections < 9 ? -1 : -2;

		name = cd->trk[num].songname ? cd->trk[num].songname : "";

		if (cur_nsections)
	        {
    			if (cd->trk[num].section > 9)
			{
				sprintf(tracknum, "%*d.%d", digits,
					cd->trk[num].track,
					cd->trk[num].section);
			} else {
				if (cd->trk[num].section)
				{
					sprintf(tracknum, "%*d.%*d", digits,
						cd->trk[num].track, sdigits,
						cd->trk[num].section);
				} else {
					sprintf(tracknum, "%*d%*s", digits,
						cd->trk[num].track,
						2 - sdigits, " ");

				}
			}
		} else {
			sprintf(tracknum, "%*d", digits, cd->trk[num].track);
		}

		if (cd->trk[num].data)
		{
			sprintf(buf, "%s) %3dMB %s", tracknum,
				cd->trk[num].length / 1024, name);
		} else {
			sprintf(buf, "%s) %02d:%02d %s", tracknum,
				cd->trk[num].length / 60,
				cd->trk[num].length % 60, name);
                }

		return (buf);
	} else {
		return (NULL);
        }
}
