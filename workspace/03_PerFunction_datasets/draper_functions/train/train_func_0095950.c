clip_line(g3s_point **p0,g3s_point **p1,ubyte codes_or)
{
	int plane_flag;
	g3s_point *old_p1;


	(*p0)->p3_flags &= ~(PF_UVS|PF_LS);
	(*p1)->p3_flags &= ~(PF_UVS|PF_LS);

	for (plane_flag=1;plane_flag<16;plane_flag<<=1)
		if (codes_or & plane_flag) {

			if ((*p0)->p3_codes & plane_flag)
				{g3s_point *t=*p0; *p0=*p1; *p1=t;}

			old_p1 = *p1;

			*p1 = clip_edge(plane_flag,*p0,*p1);

			if (old_p1->p3_flags & PF_TEMP_POINT)
				free_temp_point(old_p1);
		}

}
