shockwave_page_in()
{
	size_t i;


	for (i = 0; i < Shockwave_info.size(); i++) {
		if (Shockwave_info[i].bitmap_id >= 0) {
			bm_page_in_texture( Shockwave_info[i].bitmap_id, Shockwave_info[i].num_frames );
		} else if (Shockwave_info[i].model_id >= 0) {


			int idx = model_load( Shockwave_info[i].filename, 0, NULL );
			Assert( idx == Shockwave_info[i].model_id );

			model_page_in_textures( Shockwave_info[i].model_id );
		}
	}
}
