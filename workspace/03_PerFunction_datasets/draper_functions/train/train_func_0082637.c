make_les_entry_2d(int i, int j, int offset_i, int offset_j, int count,
		      int pos, N_les * les, N_spvector * spvect,
		      N_array_2d * cell_count, N_array_2d * status,
		      N_array_2d * start_val, double entry, int cell_type)
{
    int K;
    int di = offset_i;
    int dj = offset_j;

    K = N_get_array_2d_c_value(cell_count, i + di, j + dj) -
	N_get_array_2d_c_value(cell_count, i, j);


    if (cell_type == N_CELL_ACTIVE) {

	if (N_get_array_2d_c_value(status, i + di, j + dj) > N_CELL_ACTIVE &&
	    N_get_array_2d_c_value(status, i + di, j + dj) < N_MAX_CELL_STATE)
	    les->b[count] -=
		N_get_array_2d_d_value(start_val, i + di, j + dj) * entry;
	else if (N_get_array_2d_c_value(status, i + di, j + dj) ==
		 N_CELL_ACTIVE) {
	    if ((count + K) >= 0 && (count + K) < les->cols) {
		G_debug(5,
			" make_les_entry_2d: (N_CELL_ACTIVE) create matrix entry at row[%i] col[%i] value %g\n",
			count, count + K, entry);
		pos++;
		if (les->type == N_SPARSE_LES) {
		    spvect->index[pos] = count + K;
		    spvect->values[pos] = entry;
		}
		else {
		    les->A[count][count + K] = entry;
		}
	    }
	}
    }
    else if (cell_type == N_CELL_DIRICHLET) {

	if (N_get_array_2d_c_value(status, i + di, j + dj) > N_CELL_INACTIVE
	    && N_get_array_2d_c_value(status, i + di,
				      j + dj) < N_MAX_CELL_STATE) {
	    if ((count + K) >= 0 && (count + K) < les->cols) {
		G_debug(5,
			" make_les_entry_2d: (N_CELL_DIRICHLET) create matrix entry at row[%i] col[%i] value %g\n",
			count, count + K, entry);
		pos++;
		if (les->type == N_SPARSE_LES) {
		    spvect->index[pos] = count + K;
		    spvect->values[pos] = entry;
		}
		else {
		    les->A[count][count + K] = entry;
		}
	    }
	}
    }

    return pos;
}
