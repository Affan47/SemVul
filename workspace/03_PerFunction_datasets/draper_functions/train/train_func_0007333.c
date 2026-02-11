nm_adjust(GLEJustify jj, double *sx, double *sy, double ex, double ey, GLERectangle* r) {
	double dr, da, rz, dx, dy;
	if ((jj & 0xf000) == 0x5000) {
		double r1 = r->getWidth()/2;
		double r2 = r->getHeight()/2;
		xy_polar(*sx - ex, *sy - ey, &dr, &da);
		double xa = da - 180;
		while ((xa<0) || (xa> 180)) {
			if (xa > 180) xa = xa - 180;
			if (xa < 0) xa = xa + 180;
		}
		if (r1==0) return;
		double ca = atan(r2/r1)*180/GLE_PI;
		if (xa < 90) {
			rz = r1/cos(GLE_PI*xa/180);
			if (xa>ca) rz = r2/sin(GLE_PI*xa/180);
		} else {
			xa = xa - 90;
			rz = r2/cos(GLE_PI*xa/180);
			if (xa>(90-ca)) rz = r1/sin(GLE_PI*xa/180);
		}
		dr = dr - rz ;
		polar_xy(dr, da, &dx, &dy);
		*sx = ex + dx;
		*sy = ey + dy;
	}
	if ((jj & 0xff00) == 0x1000) {

		double rx = r->getWidth()/2;
		double ry = r->getHeight()/2;
		xy_polar(ex-(*sx), ey-(*sy), &dr, &da);
		if (fabs(rx-ry) > 1e-18) {
			double rad_alpha = GLE_PI*da/180;
			da = atan2(rx*sin(rad_alpha), ry*cos(rad_alpha))/GLE_PI*180;
		}
		polar_xy(rx, ry, da, &dx, &dy);
		*sx += dx;
		*sy += dy;
	}
}
