add_shield_point_multi(int objnum, int tri_num, vec3d *hit_pos)
{
	if (Num_multi_shield_points >= MAX_SHIELD_POINTS)
		return;

	Shield_points[Num_shield_points].objnum = objnum;
	Shield_points[Num_shield_points].shield_tri = tri_num;
	Shield_points[Num_shield_points].hit_point = *hit_pos;

	Num_multi_shield_points++;
}
