BlitPolyDirect( struct mame_bitmap *pBitmap, const INT32 *pSource, double m[4][4] )
{
	INT32 zcode;
	unsigned color = (pSource[1]<<8)&0x7f00;
	INT32 flags = pSource[3];
	int tpage = pSource[4];
	double zmin, zmax, zrep;
	struct VerTex v[5];
	int i;

	zmin = zmax = 0;

	for( i=0; i<4; i++ )
	{
		struct VerTex *pVerTex = &v[i];
		double lx = pSource[5+i*6+2];
		double ly = pSource[5+i*6+3];
		double lz = pSource[5+i*6+4];
		pVerTex->x = lx;
		pVerTex->y = ly;
		pVerTex->z = lz;
		pVerTex->u = pSource[5+i*6+0];
		pVerTex->v = pSource[5+i*6+1]+(tpage<<12);
		pVerTex->i = pSource[5+i*6+5];
		if( i==0 || pVerTex->z > zmax ) zmax = pVerTex->z;
		if( i==0 || pVerTex->z < zmin ) zmin = pVerTex->z;


		pVerTex->z = 1000;
	}
	zrep = (zmin+zmax)/2.0;
	zcode = pSource[0]+(INT32)zrep;

	mCamera.zoom = 1000;
	mCamera.cx = 640/2;
	mCamera.cy = 480/2;
	mCamera.clip.min_x = 0;
	mCamera.clip.min_y = 0;
	mCamera.clip.max_x = 640;
	mCamera.clip.max_y = 320;

	namcos22_BlitTri( pBitmap, &v[0], color, zcode, flags, &mCamera );
	v[4] = v[0];
	namcos22_BlitTri( pBitmap, &v[2], color, zcode, flags, &mCamera );
}
