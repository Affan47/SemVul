load_nebula_sub(char *filename)
{
	CFILE *fp;
	char id[16];
	int version, major;

	fp = cfopen(filename, "rb");

	if ( !fp )	{
		return 0;
	}


	cfread( id, 4, 1, fp );
	if ( strncmp( id, NEBULA_FILE_ID, 4))	{
		mprintf(( "Not a valid nebula file.\n" ));
		return 0;
	}
	cfread( &version, sizeof(int), 1, fp );
	major = version / 100;

	if ( major != NEBULA_MAJOR_VERSION )	{
		mprintf(( "An out of date nebula file.\n" ));
		return 0;
	}

	cfread( &num_pts, sizeof(int), 1, fp );
	Assert( num_pts < MAX_POINTS );
	cfread( &num_tris, sizeof(int), 1, fp );
	Assert( num_tris < MAX_TRIS );

	int i;
	for (i=0; i<num_pts; i++ )	{
		float xf, yf;
		int l;

		cfread( &xf, sizeof(float), 1, fp );
		cfread( &yf, sizeof(float), 1, fp );
		cfread( &l, sizeof(int), 1, fp );
		project_2d_onto_sphere( &nebula_vecs[i], 1.0f - xf, yf );
		vm_vec_scale( &nebula_vecs[i], 10.0f );
		nebula_verts[i].b = ubyte((l*255)/31);


	}

	for (i=0; i<num_tris; i++ )	{
		cfread( &tri[i][0], sizeof(int), 1, fp );
		cfread( &tri[i][1], sizeof(int), 1, fp );
		cfread( &tri[i][2], sizeof(int), 1, fp );
	}

	cfclose(fp);

	return 1;
}
