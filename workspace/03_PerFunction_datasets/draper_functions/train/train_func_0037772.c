create_shield_low_detail(int objnum, int model_num, matrix *orient, vec3d *centerp, vec3d *tcp, int tr0, shield_info *shieldp)
{
	matrix	tom;
	int		gi;
	int		shnum;

	shnum = get_global_shield_tri();
	Shield_hits[shnum].type = SH_TYPE_1;

	gi = get_free_global_shield_index();

	Global_tris[gi].used = 1;
	Global_tris[gi].trinum = -1;
	Global_tris[gi].creation_time = Missiontime;

	Shield_hits[shnum].tri_list[0] = gi;
	Shield_hits[shnum].num_tris = 1;
	Shield_hits[shnum].start_time = Missiontime;
	Shield_hits[shnum].objnum = objnum;

	Shield_hits[shnum].rgb[0] = 255;
	Shield_hits[shnum].rgb[1] = 255;
	Shield_hits[shnum].rgb[2] = 255;
	if((objnum >= 0) && (objnum < MAX_OBJECTS) && (Objects[objnum].type == OBJ_SHIP) && (Objects[objnum].instance >= 0) && (Objects[objnum].instance < MAX_SHIPS) && (Ships[Objects[objnum].instance].ship_info_index >= 0) && (Ships[Objects[objnum].instance].ship_info_index < Num_ship_classes)){
		ship_info *sip = &Ship_info[Ships[Objects[objnum].instance].ship_info_index];

		Shield_hits[shnum].rgb[0] = sip->shield_color[0];
		Shield_hits[shnum].rgb[1] = sip->shield_color[1];
		Shield_hits[shnum].rgb[2] = sip->shield_color[2];
	}

	vm_vector_2_matrix(&tom, &shieldp->tris[tr0].norm, NULL, NULL);

	create_low_detail_poly(gi, tcp, &tom.vec.rvec, &tom.vec.uvec);
}
