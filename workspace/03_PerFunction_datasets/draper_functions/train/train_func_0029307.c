gf_sg_route_del_by_id(GF_SceneGraph *sg,u32 routeID)
{
	GF_Route *r;
	if(!sg) return GF_BAD_PARAM;
	r = gf_sg_route_find(sg, routeID);
	if (!r) return GF_BAD_PARAM;
	gf_sg_route_del(r);
	return GF_OK;
}
