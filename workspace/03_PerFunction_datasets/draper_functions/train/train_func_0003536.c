blipDrawDistorted(blip *b, vec3d *pos)
{
	float scale;
	float dist=vm_vec_normalize(pos);
	vec3d out;
	float distortion_angle=20;


	if(emp_active_local()){
		scale = emp_current_intensity();
		distortion_angle *= frand_range(-3.0f,3.0f)*frand_range(0.0f, scale);
		dist *= frand_range(MAX(0.75f, 0.75f*scale), MIN(1.25f, 1.25f*scale));

		if (dist > 1.25f) dist = 1.25f;
		if (dist < 0.75f) dist = 0.75f;
	}

	vm_vec_random_cone(&out,pos,distortion_angle);
	vm_vec_scale(&out,dist);

    if (Cmdline_nohtl)
    {
	    drawContact(&out,b->rad);
    }
    else
    {
        drawContactHtl(&out,b->rad);
    }
}
