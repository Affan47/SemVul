drawBlipsSorted(int distort)
{
	matrix base_tilt = vmd_identity_matrix;

	vm_angle_2_matrix(&base_tilt, -PI/6, 0);

	for(int is_bright = 0; is_bright < 2; is_bright++) {
		sub_y_clip = true;
		g3_start_instance_matrix(&vmd_zero_vector, &base_tilt, true);
			drawBlips(BLIP_TYPE_BOMB, is_bright, distort);
			drawBlips(BLIP_TYPE_JUMP_NODE, is_bright, distort);
			drawBlips(BLIP_TYPE_NORMAL_SHIP, is_bright, distort);
			drawBlips(BLIP_TYPE_TAGGED_SHIP, is_bright, distort);
			drawBlips(BLIP_TYPE_WARPING_SHIP, is_bright, distort);
			drawBlips(BLIP_TYPE_NAVBUOY_CARGO, is_bright, distort);
		g3_done_instance(true);

		drawOutlinesHtl();

		sub_y_clip = false;
		g3_start_instance_matrix(&vmd_zero_vector, &base_tilt, true);
			drawBlips(BLIP_TYPE_BOMB, is_bright, distort);
			drawBlips(BLIP_TYPE_JUMP_NODE, is_bright, distort);
			drawBlips(BLIP_TYPE_NORMAL_SHIP, is_bright, distort);
			drawBlips(BLIP_TYPE_TAGGED_SHIP, is_bright, distort);
			drawBlips(BLIP_TYPE_WARPING_SHIP, is_bright, distort);
			drawBlips(BLIP_TYPE_NAVBUOY_CARGO, is_bright, distort);
		g3_done_instance(true);
	}
}
