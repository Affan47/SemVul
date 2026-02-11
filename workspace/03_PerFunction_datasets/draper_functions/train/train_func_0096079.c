beam_get_cone_dot(beam *b)
{
	switch(b->type){
	case BEAM_TYPE_A:
	case BEAM_TYPE_C:
	case BEAM_TYPE_D:
	case BEAM_TYPE_E:

		return (float)cos(fl_radians(50.5f));

	case BEAM_TYPE_B:
		return vm_vec_dotprod(&b->binfo.dir_a, &b->binfo.dir_b);

	default:
		Int3();
	}

	Int3();
	return 0.0f;
}
