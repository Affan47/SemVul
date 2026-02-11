debris_page_in()
{
	uint i;

	Debris_model = model_load( NOX("debris01.pof"), 0, NULL );
	if (Debris_model >= 0)	{
		polymodel * pm;
		pm = model_get(Debris_model);
		Debris_num_submodels = pm->n_models;
	}

	Debris_vaporize_model = model_load( NOX("debris02.pof"), 0, NULL );

	for (i=0; i<Species_info.size(); i++ )
	{
		species_info *species = &Species_info[i];

		nprintf(( "Paging", "Paging in debris texture '%s'\n", species->debris_texture.filename));

		species->debris_texture.bitmap_id = bm_load(species->debris_texture.filename);
		if (species->debris_texture.bitmap_id < 0)
		{
			Warning( LOCATION, "Couldn't load species %s debris\ntexture, '%s'\n", species->species_name, species->debris_texture.filename);
		}

		bm_page_in_texture(species->debris_texture.bitmap_id);
	}

}
