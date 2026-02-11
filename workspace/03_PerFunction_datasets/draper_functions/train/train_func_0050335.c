compositor_background_modified(GF_Node *node)
{
	M_Background *bck = (M_Background *)node;
	BackgroundStack *st = (BackgroundStack *) gf_node_get_private(node);
	if (!st) return;

	if (!gf_sg_vrml_field_equal(&bck->skyColor, &st->sky_col, GF_SG_VRML_MFCOLOR)
		|| !gf_sg_vrml_field_equal(&bck->skyAngle, &st->sky_ang, GF_SG_VRML_MFFLOAT)
		) {

		if (st->sky_mesh) mesh_free(st->sky_mesh);
		st->sky_mesh = NULL;
		gf_sg_vrml_field_copy(&st->sky_col, &bck->skyColor, GF_SG_VRML_MFCOLOR);
		gf_sg_vrml_field_copy(&st->sky_ang, &bck->skyAngle, GF_SG_VRML_MFFLOAT);
	}
	if (!gf_sg_vrml_field_equal(&bck->groundColor, &st->ground_col, GF_SG_VRML_MFCOLOR)
		|| !gf_sg_vrml_field_equal(&bck->groundAngle, &st->ground_ang, GF_SG_VRML_MFFLOAT)
		) {

		if (st->ground_mesh) mesh_free(st->ground_mesh);
		st->ground_mesh = NULL;
		gf_sg_vrml_field_copy(&st->ground_col, &bck->groundColor, GF_SG_VRML_MFCOLOR);
		gf_sg_vrml_field_copy(&st->ground_ang, &bck->groundAngle, GF_SG_VRML_MFFLOAT);
	}

	back_check_gf_sc_texture_change(&st->txh_front, &bck->frontUrl);
	back_check_gf_sc_texture_change(&st->txh_back, &bck->backUrl);
	back_check_gf_sc_texture_change(&st->txh_top, &bck->topUrl);
	back_check_gf_sc_texture_change(&st->txh_bottom, &bck->bottomUrl);
	back_check_gf_sc_texture_change(&st->txh_left, &bck->leftUrl);
	back_check_gf_sc_texture_change(&st->txh_right, &bck->rightUrl);


	gf_sc_invalidate(st->compositor, NULL);
}
