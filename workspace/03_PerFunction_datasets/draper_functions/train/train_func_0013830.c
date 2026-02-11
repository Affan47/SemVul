vm_vec_unrotate(vec3d *dest,vec3d *src,matrix *m)
{
	Assert(dest != src);

	dest->xyz.x = (src->xyz.x*m->vec.rvec.xyz.x)+(src->xyz.y*m->vec.uvec.xyz.x)+(src->xyz.z*m->vec.fvec.xyz.x);
	dest->xyz.y = (src->xyz.x*m->vec.rvec.xyz.y)+(src->xyz.y*m->vec.uvec.xyz.y)+(src->xyz.z*m->vec.fvec.xyz.y);
	dest->xyz.z = (src->xyz.x*m->vec.rvec.xyz.z)+(src->xyz.y*m->vec.uvec.xyz.z)+(src->xyz.z*m->vec.fvec.xyz.z);

	return dest;
}
