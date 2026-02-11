gf_bbox_grow_point(GF_BBox *box, GF_Vec pt)
{
	if (pt.x > box->max_edge.x) box->max_edge.x = pt.x;
	if (pt.y > box->max_edge.y) box->max_edge.y = pt.y;
	if (pt.z > box->max_edge.z) box->max_edge.z = pt.z;
	if (pt.x < box->min_edge.x) box->min_edge.x = pt.x;
	if (pt.y < box->min_edge.y) box->min_edge.y = pt.y;
	if (pt.z < box->min_edge.z) box->min_edge.z = pt.z;
}
