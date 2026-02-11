GradientGetMatrix(GF_Node *transform, GF_Matrix2D *mat)
{
	gf_mx2d_init(*mat);
	if (transform) {
		switch (gf_node_get_tag(transform) ) {
		case TAG_MPEG4_Transform2D:
		{
			M_Transform2D *tr = (M_Transform2D *)transform;
			gf_mx2d_add_scale_at(mat, 0, 0, tr->scale.x, tr->scale.y, tr->scaleOrientation);
			gf_mx2d_add_rotation(mat, tr->center.x, tr->center.y, tr->rotationAngle);
			gf_mx2d_add_translation(mat, tr->translation.x, tr->translation.y);
		}
			break;
		case TAG_MPEG4_TransformMatrix2D:
		{
			M_TransformMatrix2D *tm = (M_TransformMatrix2D*)transform;
			gf_mx2d_init(*mat);
			mat->m[0] = tm->mxx; mat->m[1] = tm->mxy; mat->m[2] = tm->tx;
			mat->m[3] = tm->myx; mat->m[4] = tm->myy; mat->m[5] = tm->ty;
		}
			break;
		default:
			break;
		}
	}
}
