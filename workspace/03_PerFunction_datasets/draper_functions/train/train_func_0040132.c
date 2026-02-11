gf_sc_reset_graphics(GF_Compositor *compositor)
{
	if (compositor) {
		Bool locked = gf_mx_try_lock(compositor->mx);
		compositor->reset_graphics = 1;
		if (locked) gf_mx_v(compositor->mx);
	}
}
