compositor_svg_apply_local_transformation(GF_TraverseState *tr_state, SVGAllAttributes *atts, GF_Matrix2D *backup_matrix_2d, GF_Matrix *backup_matrix)
{
#ifndef GPAC_DISABLE_3D
	if (tr_state->visual->type_3d && backup_matrix) {
		GF_Matrix tmp;
		Bool is_draw = (tr_state->traversing_mode==TRAVERSE_SORT) ? 1 : 0;
		gf_mx_copy(*backup_matrix, tr_state->model_matrix);

		if (is_draw) visual_3d_matrix_push(tr_state->visual);

		if (atts->transform && atts->transform->is_ref) {
			gf_mx_from_mx2d(&tr_state->model_matrix, &tr_state->vb_transform);
			if (is_draw) {
				GF_Matrix tmp;
				gf_mx_init(tmp);
				gf_mx_add_translation(&tmp, -tr_state->camera->width/2, tr_state->camera->height/2, 0);
				gf_mx_add_scale(&tmp, FIX_ONE, -FIX_ONE, FIX_ONE);
				gf_mx_add_matrix(&tmp, &tr_state->model_matrix);
				visual_3d_matrix_load(tr_state->visual, tmp.m);
			}
		}

		if (atts->motionTransform) {
			if (is_draw) {
				gf_mx_from_mx2d(&tmp, atts->motionTransform);
				visual_3d_matrix_add(tr_state->visual, tmp.m);
			} else {
				gf_mx_add_matrix_2d(&tr_state->model_matrix, atts->motionTransform);
			}
		}

		if (atts->transform) {
			if (is_draw) {
				gf_mx_from_mx2d(&tmp, &atts->transform->mat);
				visual_3d_matrix_add(tr_state->visual, tmp.m);
			} else {
				gf_mx_add_matrix_2d(&tr_state->model_matrix, &atts->transform->mat);
			}
		}
		return;
	}
#endif
	gf_mx2d_copy(*backup_matrix_2d, tr_state->transform);

	if (atts->transform && atts->transform->is_ref)
		gf_mx2d_copy(tr_state->transform, tr_state->vb_transform);

	if (atts->motionTransform)
		gf_mx2d_pre_multiply(&tr_state->transform, atts->motionTransform);

	if (atts->transform)
		gf_mx2d_pre_multiply(&tr_state->transform, &atts->transform->mat);

}
