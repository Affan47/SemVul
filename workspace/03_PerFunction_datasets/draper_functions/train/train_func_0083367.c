gf_sc_set_scene_size(GF_Compositor *compositor, u32 Width, u32 Height, Bool force_size)
{
	if (!Width || !Height) {
		if (compositor->override_size_flags) {

			compositor->scene_height = SC_DEF_HEIGHT;
			compositor->scene_width = SC_DEF_WIDTH;
		} else {

			compositor->scene_width = compositor->new_width ? compositor->new_width : compositor->display_width;
			compositor->scene_height = compositor->new_height ? compositor->new_height : compositor->display_height;
		}
	} else {
		compositor->scene_height = Height;
		compositor->scene_width = Width;
	}
	if (force_size)
		compositor->has_size_info = 1;
	return GF_OK;
}
