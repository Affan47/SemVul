gf_mx_ortho(GF_Matrix *mx, Fixed left, Fixed right, Fixed bottom, Fixed top, Fixed z_near, Fixed z_far)
{
	gf_mx_init(*mx);
	mx->m[0] = gf_divfix(2*FIX_ONE, right-left);
	mx->m[5] = gf_divfix(2*FIX_ONE, top-bottom);
	mx->m[10] = gf_divfix(-2*FIX_ONE, z_far-z_near);
	mx->m[12] = gf_divfix(right+left, right-left);
	mx->m[13] = gf_divfix(top+bottom, top-bottom);
	mx->m[14] = gf_divfix(z_far+z_near, z_far-z_near);
	mx->m[15] = FIX_ONE;
}
