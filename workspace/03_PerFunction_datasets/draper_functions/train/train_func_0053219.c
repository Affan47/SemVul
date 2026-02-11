generic_anim_unload(generic_anim *ga)
{
	if(ga->num_frames > 0) {
		if(ga->streaming) {
			if(ga->type == BM_TYPE_ANI) {
				anim_free(ga->ani.animation);
				free_anim_instance(ga->ani.instance);
			}
			if(ga->type == BM_TYPE_EFF) {
				if(ga->eff.next_frame >= 0)
					bm_release(ga->eff.next_frame);
				if(ga->bitmap_id >= 0)
					bm_release(ga->bitmap_id);
			}
		}
		else {

			bm_release(ga->first_frame);
		}
		if(ga->buffer) {
			bm_release(ga->bitmap_id);
		}
	}
	generic_anim_init(ga, NULL);
}
