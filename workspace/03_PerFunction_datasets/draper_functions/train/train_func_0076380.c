mc_ray_boundingbox( vec3d *min, vec3d *max, vec3d * p0, vec3d *pdir, vec3d *hitpos )
{

	vec3d tmp_hitpos;
	if ( hitpos == NULL )	{
		hitpos = &tmp_hitpos;
	}


	if ( Mc->flags & MC_CHECK_SPHERELINE )	{


		vec3d sphere_mod_min, sphere_mod_max;

		sphere_mod_min.xyz.x = min->xyz.x - Mc->radius;
		sphere_mod_max.xyz.x = max->xyz.x + Mc->radius;
		sphere_mod_min.xyz.y = min->xyz.y - Mc->radius;
		sphere_mod_max.xyz.y = max->xyz.y + Mc->radius;
		sphere_mod_min.xyz.z = min->xyz.z - Mc->radius;
		sphere_mod_max.xyz.z = max->xyz.z + Mc->radius;

		return fvi_ray_boundingbox( &sphere_mod_min, &sphere_mod_max, p0, pdir, hitpos );
	} else {
		return fvi_ray_boundingbox( min, max, p0, pdir, hitpos );
	}
}
