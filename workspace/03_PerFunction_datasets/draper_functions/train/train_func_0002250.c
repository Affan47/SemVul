vimoswcsrange (vimoswcs, ra1, ra2, dec1, dec2)

struct WorldCoor *vimoswcs;
double	*ra1;
double	*ra2;
double	*dec1;
double	*dec2;

{
    double xpos1, xpos2, xpos3, xpos4, ypos1, ypos2, ypos3, ypos4;

    if (isvimoswcs(vimoswcs)) {


	(void) pix2vimoswcs (vimoswcs,1.0,1.0,&xpos1,&ypos1);
	(void) pix2vimoswcs (vimoswcs,1.0,vimoswcs->nypix,&xpos2,&ypos2);
	(void) pix2vimoswcs (vimoswcs,vimoswcs->nxpix,1.0,&xpos3,&ypos3);
	(void) pix2vimoswcs (vimoswcs,vimoswcs->nxpix,vimoswcs->nypix,&xpos4,&ypos4);


	*ra1 = xpos1;
	if (xpos2 < *ra1) *ra1 = xpos2;
	if (xpos3 < *ra1) *ra1 = xpos3;
	if (xpos4 < *ra1) *ra1 = xpos4;


	*ra2 = xpos1;
	if (xpos2 > *ra2) *ra2 = xpos2;
	if (xpos3 > *ra2) *ra2 = xpos3;
	if (xpos4 > *ra2) *ra2 = xpos4;


	*dec1 = ypos1;
	if (ypos2 < *dec1) *dec1 = ypos2;
	if (ypos3 < *dec1) *dec1 = ypos3;
	if (ypos4 < *dec1) *dec1 = ypos4;


	*dec2 = ypos1;
	if (ypos2 > *dec2) *dec2 = ypos2;
	if (ypos3 > *dec2) *dec2 = ypos3;
	if (ypos4 > *dec2) *dec2 = ypos4;
	}

    else {
	*ra1 = 0.0;
	*ra2 = 0.0;
	*dec1 = 0.0;
	*dec2 = 0.0;
	}

    return;
}
