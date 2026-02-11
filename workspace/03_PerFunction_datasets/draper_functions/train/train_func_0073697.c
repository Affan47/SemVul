_set_min_max_of_grid(int dim, int curr,
				 int *start,
				 int *end,
				 int *min,
				 int *max,
				 int *pos,
				 int dims)
{
	int i;
	int start_curr = curr;

	for (pos[dim]=start[dim]; pos[dim]<=end[dim]; pos[dim]++) {
		curr = start_curr + (pos[dim] * offset[dim]);
		if (dim == (dims-1)) {
			if (!bit_test(bit_grid, curr))
				continue;
			for(i = 0; i<dims; i++) {
				min[i] = MIN(min[i], pos[i]);
				max[i] = MAX(max[i], pos[i]);
			}
		} else
			_set_min_max_of_grid(dim+1, curr, start, end,
					     min, max, pos, dims);
	}
}
