m_pc(union DateData *x)
{
    if (simple_dat_p(x)) {
	get_s_civil(x);
	return x->s.pc;
    }
    else {
	get_c_civil(x);
	get_c_time(x);
	return x->c.pc;
    }
}
