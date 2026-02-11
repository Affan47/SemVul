ct_update_ABtrails(ship *shipp)
{
	vec3d v1;
	int idx;
	ship_info *sip;
	object *objp;


	Assert(shipp != NULL);
	Assert(shipp->objnum >= 0);
	Assert(shipp->ship_info_index >= 0);
	objp = &Objects[shipp->objnum];
	sip = &Ship_info[shipp->ship_info_index];


	if (sip->afterburner_trail.bitmap_id < 0)
		return;

	for(idx=0; idx<MAX_SHIP_CONTRAILS; idx++){
		if(objp->phys_info.flags & PF_AFTERBURNER_ON){
			if(shipp->ABtrail_ptr[idx] != NULL){

				vm_vec_unrotate(&v1, &shipp->ab_info[idx].pt, &objp->orient);
				vm_vec_add2(&v1, &objp->pos);


				if(trail_stamp_elapsed(shipp->ABtrail_ptr[idx])){
					trail_add_segment(shipp->ABtrail_ptr[idx], &v1);
					trail_set_stamp(shipp->ABtrail_ptr[idx]);
				} else {
					trail_set_segment(shipp->ABtrail_ptr[idx], &v1);
				}
			}
		}

	}
}
