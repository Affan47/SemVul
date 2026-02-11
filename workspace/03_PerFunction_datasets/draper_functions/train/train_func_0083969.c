rc_getvec_n(int i)
{
	if (i < 0) return NULL;
	switch (rcvars[i].type)
	{
	case rcv_int:
	case rcv_bool:
	case rcv_vector:
		return (int *)rcvars[i].mem;
	}
	return NULL;
}
