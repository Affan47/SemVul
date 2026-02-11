pop_unsent_buffer(unsent_buffer *ub)
{
	if(ub && ub->bufs && ub->sz) {
		size_t sz;
		for(sz=0; sz<ub->sz; ++sz) {
			if(ub->bufs[sz]) {
				ub->bufs[sz] = NULL;
				break;
			}
		}
	}
}
