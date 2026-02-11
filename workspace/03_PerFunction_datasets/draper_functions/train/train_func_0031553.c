getFirepointStatus() {

	ship_info* pship;
	ship* shipp;
	polymodel* pm;

	Assert(Objects[Player->objnum].type == OBJ_SHIP);

	if (Objects[Player->objnum].type == OBJ_SHIP) {
		shipp = &Ships[Objects[Player->objnum].instance];
		pship = &Ship_info[shipp->ship_info_index];


		pm = model_get(pship->model_num);

		if (pm->n_guns > 0) {
			eye eyepoint = pm->view_positions[shipp->current_viewpoint];
			vec2d ep = {eyepoint.pnt.xyz.x, eyepoint.pnt.xyz.y};

			for (int i = 0; i < pm->n_guns; i++) {
				int isactive = 0;

				if ( !timestamp_elapsed(shipp->weapons.next_primary_fire_stamp[i]) )
					isactive = 1;
				else if (timestamp_elapsed(shipp->weapons.primary_animation_done_time[i]))
					isactive = 1;
				else if (i == shipp->weapons.current_primary_bank || shipp->flags & SF_PRIMARY_LINKED)
					isactive = 2;

				for (int j = 0; j < pm->gun_banks[i].num_slots; j++) {
					firepoint tmp = { {ep.x - pm->gun_banks[i].pnt[j].xyz.x, ep.y - pm->gun_banks[i].pnt[j].xyz.y}, isactive};
					fp.push_back(tmp);
				}
			}
		}
	}
}
