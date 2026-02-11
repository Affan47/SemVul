shockwave_level_init()
{
	int i;

	if ( !Default_shockwave_loaded ) {
		i = -1;


		if ( Cmdline_enable_3d_shockwave && cf_exists_full(Default_shockwave_3D_filename, CF_TYPE_MODELS) ) {
			mprintf(("SHOCKWAVE =>  Loading default shockwave model... \n"));

			i = shockwave_load( Default_shockwave_3D_filename, true );

			if (i >= 0)
				mprintf(("SHOCKWAVE =>  Default model load: SUCCEEDED!!\n"));
			else
				mprintf(("SHOCKWAVE =>  Default model load: FAILED!!  Falling back to 2D effect...\n"));
		}


		if (i < 0 || Cmdline_fb_explosions) {
			mprintf(("SHOCKWAVE =>  Loading default shockwave animation... \n"));

			i = shockwave_load( Default_shockwave_2D_filename );

			if (i >= 0)
				mprintf(("SHOCKWAVE =>  Default animation load: SUCCEEDED!!\n"));
			else
				mprintf(("SHOCKWAVE =>  Default animation load: FAILED!!  Checking if 3d effect was already tried...\n"));
		}


		if ( i < 0 && !Cmdline_enable_3d_shockwave && cf_exists_full(Default_shockwave_3D_filename, CF_TYPE_MODELS) ) {
			mprintf(("SHOCKWAVE =>  Loading default shockwave model as last resort... \n"));

			i = shockwave_load( Default_shockwave_3D_filename, true );

			if (i >= 0)
				mprintf(("SHOCKWAVE =>  Default model load: SUCCEEDED!!\n"));
			else
				mprintf(("SHOCKWAVE =>  Default model load: FAILED!!  No effect loaded...\n"));
		}

		if (i < 0)
			Error(LOCATION, "ERROR:  Unable to open neither 3D nor 2D default shockwaves!!");

		Default_shockwave_loaded = 1;
	} else {


		if (Shockwave_info[0].model_id >= 0)
			Shockwave_info[0].model_id = model_load( Default_shockwave_3D_filename, 0, NULL );
	}

	Assert( ((Shockwave_info[0].bitmap_id >= 0) || (Shockwave_info[0].model_id >= 0)) );

	list_init(&Shockwave_list);

	for ( i = 0; i < MAX_SHOCKWAVES; i++ ) {
		Shockwaves[i].flags = 0;
		Shockwaves[i].objnum = -1;
		Shockwaves[i].model_id = -1;
	}

	Shockwave_inited = 1;
}
