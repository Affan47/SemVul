datetime_to_time(VALUE self)
{
    volatile VALUE dup = dup_obj_with_new_offset(self, 0);
    {
	VALUE t;

	get_d1(dup);

	t = f_utc6(rb_cTime,
		   m_real_year(dat),
		   INT2FIX(m_mon(dat)),
		   INT2FIX(m_mday(dat)),
		   INT2FIX(m_hour(dat)),
		   INT2FIX(m_min(dat)),
		   f_add(INT2FIX(m_sec(dat)),
			 m_sf_in_sec(dat)));
	return f_getlocal(t);
    }
}
