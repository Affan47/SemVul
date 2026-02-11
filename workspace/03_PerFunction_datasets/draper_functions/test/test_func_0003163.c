hkl_geometry_list_sort(HklGeometryList *self, HklGeometry *ref)
{
	size_t len = HKL_LIST_LEN(self->items);
	double *distances = alloca(len * sizeof(*distances));
	size_t *idx = alloca(len * sizeof(*idx));
	size_t i, x;
	int j, p;
	HklGeometryListItem **items;


	for(i=0; i<len; ++i){
		distances[i] = hkl_geometry_distance(ref, self->items[i]->geometry);
		idx[i] = i;
	}


	for(i=1; i<len; ++i){
		x = idx[i];

		for(p = 0; distances[idx[p]] < distances[x] && fabs(distances[idx[p]] - distances[x]) > HKL_EPSILON; p++);


		for(j=i-1; j>=p; j--)
			idx[j+1] = idx[j];

		idx[p] = x;
	}


	items = malloc(len * sizeof(HklGeometryListItem *));
	for(i=0; i<len; ++i)
		items[i] = self->items[idx[i]];
	free(self->items);
	self->items = items;
}
