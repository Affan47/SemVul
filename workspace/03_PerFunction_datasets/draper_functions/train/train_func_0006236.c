enable_collision_info(  bool points, bool normals, bool metadata, bool pen_depth)
{
	impl->collision_info_points = points;
	impl->collision_info_normals = normals;
	impl->collision_info_meta = metadata;
	impl->collision_info_pen_depth = pen_depth;
	impl->collision_info_collect = points || normals || metadata || pen_depth;
}
