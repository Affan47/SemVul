vm_vec_copy_normalize(vms_vector *dest,vms_vector *src)
{
	fix m;

	m = vm_vec_mag(src);

	if (m > 0) {
		dest->x = fixdiv(src->x,m);
		dest->y = fixdiv(src->y,m);
		dest->z = fixdiv(src->z,m);
	}

	return m;
}
