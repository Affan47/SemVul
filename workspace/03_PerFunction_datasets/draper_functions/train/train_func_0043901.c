brief_set_camera_target(vec3d *pos, matrix *orient, int time)
{
	float time_in_seconds;

	time_in_seconds = time / 1000.0f;

	if ( time == 0 ) {
		Current_cam_pos = *pos;
		Current_cam_orient = *orient;
	}

	Target_cam_pos = *pos;
	Target_cam_orient = *orient;
	Start_cam_orient = Current_cam_orient;
	Start_cam_pos = Current_cam_pos;
	Start_cam_move = timer_get_milliseconds()*1000.0f;
	Total_move_time = time_in_seconds;
	Elapsed_time = 0.0f;

	vm_vec_scale_add(&Start_lookat_pos, &Start_cam_pos, &Start_cam_orient.vec.fvec, LOOKAT_DIST);
	vm_vec_scale_add(&Target_lookat_pos, &Target_cam_pos, &Target_cam_orient.vec.fvec, LOOKAT_DIST);

	Play_highlight_flag = 1;
	Cam_target_reached = 0;
	Cam_movement_done=0;
	anim_release_all_instances(ON_BRIEFING_SELECT);


	vm_vec_sub(&Cam_vel, pos, &Current_cam_pos);

	if ( !IS_VEC_NULL_SQ_SAFE(&Cam_vel) ) {
		vm_vec_normalize(&Cam_vel);
	}


	vm_vec_sub(&Lookat_vel, &Target_lookat_pos, &Current_lookat_pos);
	vm_vec_scale(&Lookat_vel, 1.0f/time_in_seconds);

	Start_dist = vm_vec_dist(&Start_cam_pos, &Start_lookat_pos);
	End_dist = vm_vec_dist(&Target_cam_pos, &Target_lookat_pos);
	Dist_change_rate = (End_dist - Start_dist) / time_in_seconds;

	Total_dist=vm_vec_dist(&Start_cam_pos, &Target_cam_pos);

	Peak_speed=Total_dist/Total_move_time*2.0f;
	Cam_accel = 4*Total_dist/(Total_move_time*Total_move_time);
	Last_dist=0.0f;

	vm_vec_zero(&W_init);

	get_camera_limits(&Start_cam_orient, &Target_cam_orient, Total_move_time, &Acc_limit, &Vel_limit);
}
