model_octant_find_faces_sub(polymodel * pm, model_octant * oct, void *model_ptr, int just_count )
{
	ubyte *p = (ubyte *)model_ptr;
	int chunk_type, chunk_size;

	chunk_type = w(p);
	chunk_size = w(p+4);

	while (chunk_type != OP_EOF)	{

		switch (chunk_type) {
		case OP_EOF:			return 1;
		case OP_DEFPOINTS:
			moff_defpoints(p, just_count);
			break;
		case OP_FLATPOLY:		moff_flatpoly(p, pm, oct, just_count ); break;
		case OP_TMAPPOLY:		moff_tmappoly(p, pm, oct, just_count ); break;
		case OP_SORTNORM:		{
				int frontlist = w(p+36);
				int backlist = w(p+40);
				int prelist = w(p+44);
				int postlist = w(p+48);
				int onlist = w(p+52);

				if (prelist) model_octant_find_faces_sub(pm,oct,p+prelist,just_count);
				if (backlist) model_octant_find_faces_sub(pm,oct,p+backlist,just_count);
				if (onlist) model_octant_find_faces_sub(pm,oct,p+onlist,just_count);
				if (frontlist) model_octant_find_faces_sub(pm,oct,p+frontlist,just_count);
				if (postlist) model_octant_find_faces_sub(pm,oct,p+postlist,just_count);
			}
			break;
		case OP_BOUNDBOX:		break;
		default:
			mprintf(( "Bad chunk type %d, len=%d in model_octant_find_faces_sub\n", chunk_type, chunk_size ));
			Int3();
			return 0;
		}
		p += chunk_size;
		chunk_type = w(p);
		chunk_size = w(p+4);
	}
	return 1;
}
