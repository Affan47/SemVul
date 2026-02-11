gar_parse_subdiv(struct gar_subdiv *gsub, struct tre_subdiv_t *sub)
{
	u_int32_t cx,cy;
	u_int32_t width, height;

	gsub->terminate = sub->terminate;
	gsub->rgn_start    = get_u24(&sub->rgn_offset);
	log(14, "rgn_start: %04X terminate=%d elements=%x\n", gsub->rgn_start, gsub->terminate,sub->elements);

	gsub->haspoints  = !!(sub->elements & 0x10);
	gsub->hasidxpoints = !!(sub->elements & 0x20);
	gsub->haspolylines = !!(sub->elements & 0x40);
	gsub->haspolygons = !!(sub->elements & 0x80);

	cx = get_u24(&sub->center_lng);
	gsub->icenterlng = SIGN3B(cx);
	cy = get_u24(&sub->center_lat);
	gsub->icenterlat = SIGN3B(cy);
	width	= sub->width & 0x7fff;
	height	= sub->height;
	width  <<= gsub->shift;
	height <<= gsub->shift;

	gsub->north = gsub->icenterlat + height;
	gsub->south = gsub->icenterlat - height;
	gsub->east  = gsub->icenterlng + width;
	gsub->west  = gsub->icenterlng - width;
	if (gsub->south > gsub->north || gsub->west > gsub->east)
		log(1, "Invalid Subdiv North: %fC, East: %fC, South: %fC, West: %fC cx=%d cy=%d\n",
			GARDEG(gsub->north),
			GARDEG(gsub->east),
			GARDEG(gsub->south),
			GARDEG(gsub->west),
			gsub->icenterlng, gsub->icenterlat);
	log(13, "Subdiv North: %fC, East: %fC, South: %fC, West: %fC cx=%d cy=%d\n",
		GARDEG(gsub->north),
		GARDEG(gsub->east),
		GARDEG(gsub->south),
		GARDEG(gsub->west),
		gsub->icenterlng, gsub->icenterlat);
}
