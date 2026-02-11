gf_mx_apply_bbox(GF_Matrix *mx, GF_BBox *box)
{
	u32 i;
	GF_Vec v[4];
	v[0] = box->min_edge;
	v[1] = box->min_edge; v[1].x = box->max_edge.x;
	v[2] = box->min_edge; v[2].y = box->max_edge.y;
	v[3] = box->min_edge; v[3].z = box->max_edge.z;
	box->max_edge.x = box->max_edge.y = box->max_edge.z = -FIX_MAX;
	box->min_edge.x = box->min_edge.y = box->min_edge.z = FIX_MAX;
	for (i=0;i<4; i++) {
		gf_mx_apply_vec(mx, &v[i]);
		if (box->min_edge.x > v[i].x) box->min_edge.x = v[i].x;
		if (box->min_edge.y > v[i].y) box->min_edge.y = v[i].y;
		if (box->min_edge.z > v[i].z) box->min_edge.z = v[i].z;
		if (box->max_edge.x < v[i].x) box->max_edge.x = v[i].x;
		if (box->max_edge.y < v[i].y) box->max_edge.y = v[i].y;
		if (box->max_edge.z < v[i].z) box->max_edge.z = v[i].z;
	}
	gf_bbox_refresh(box);
}
