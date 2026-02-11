model_interp_sortnorm_f2b(ubyte * p,polymodel * pm, bsp_info *sm, int do_box_check)
{
	#ifndef NDEBUG
	modelstats_num_sortnorms++;
	#endif

	int frontlist = w(p+36);
	int backlist = w(p+40);
	int prelist = w(p+44);
	int postlist = w(p+48);
	int onlist = w(p+52);

	if (postlist) model_interp_sub(p+postlist,pm,sm,do_box_check);

	if (g3_check_normal_facing(vp(p+20),vp(p+8))) {

		if (frontlist) model_interp_sub(p+frontlist,pm,sm,do_box_check);

		if (onlist) model_interp_sub(p+onlist,pm,sm,do_box_check);

		if (backlist) model_interp_sub(p+backlist,pm,sm,do_box_check);

	}	else {


		if (backlist) model_interp_sub(p+backlist,pm,sm,do_box_check);

		if (onlist) model_interp_sub(p+onlist,pm,sm,do_box_check);

		if (frontlist) model_interp_sub(p+frontlist,pm,sm,do_box_check);

	}

	if (prelist) model_interp_sub(p+prelist,pm,sm,do_box_check);
}
