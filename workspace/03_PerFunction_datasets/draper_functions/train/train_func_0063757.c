endExecuteBlock() {
	if (nx==0 || ny==0) {

		nx = ny = 2;
		alloc_zdata(nx,ny);
		z[0] = z[1] = z[2] = z[3] = -GLE_INF;
	}
	if (zclipminset || zclipmaxset) {
		for (int li = 0; li< nx*ny; li++) {
			if (zclipminset) if (z[li]<zclipmin) z[li] = zclipmin;
			if (zclipmaxset) if (z[li]>zclipmax) z[li] = zclipmax;
		}
		if (zclipminset) zmin = zclipmin;
		if (zclipmaxset) zmax = zclipmax;
	}
	hide_enddefaults();
	if (sf.zaxis.min != sf.zaxis.max) {
		zmin = sf.zaxis.min;
		zmax = sf.zaxis.max;
	}
	sf.nx = nx;
	sf.ny = ny;
	sf.z = z;
	sf.zmin = zmin;
	sf.zmax = zmax;
	hide(z,nx,ny,zmin,zmax,&sf);
	g_move(m_origin);
}
