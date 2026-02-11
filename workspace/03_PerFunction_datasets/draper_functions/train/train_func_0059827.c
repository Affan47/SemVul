col_convert(col *cp, double *wp) {

	if ((cp->t & T_XYZ) == 0 || (cp->t & T_N) == 0)
		error("gen_color needs XYZ and device colors set !");

	if ((cp->t & T_LAB) == 0) {
		icmXYZNumber w;
		w.X = wp[0];
		w.Y = wp[1];
		w.Z = wp[2];
		icmXYZ2Lab(&w, cp->Lab, cp->XYZ);
		cp->t |= T_LAB;
	}
	if ((cp->t & T_DEN) == 0) {
		icx_XYZ2Tdens(cp->den, cp->XYZ);

#ifdef DEN_COMPRESS

		{
			int e;
			for (e = 0; e < 3; e++) {
				if (cp->den[e] > 1.0)
					cp->den[e] = 1.0 + (cp->den[e] - 1.0) * 0.5;
			}
		}
#endif
		cp->t |= T_DEN;
	}

	if ((cp->t & T_RGB) == 0) {
		icx_XYZ2sRGB(cp->rgb, wp, cp->XYZ);
		cp->t |= T_RGB;
	}
}
