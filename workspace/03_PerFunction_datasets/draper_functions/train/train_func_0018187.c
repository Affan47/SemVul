free_jisyo()
{
    size_t x;

    if (ary_charalloc) {
	for (x = 0; x <= ary_cur_charalloc; x ++) {
	    free(ary_charalloc[x]);
	}
    }

    if (ary_cellalloc) {
	for (x = 0; x <= ary_cur_cellalloc; x ++) {
	    free(ary_cellalloc[x]);
	}
    }

    free(ary_charalloc);
    free(ary_cellalloc);

    ary_charalloc = NULL;
    ary_cellalloc = NULL;
    ary_size_charalloc = -1;
    ary_cur_charalloc = -1;
    ary_size_cellalloc = -1;
    ary_cur_cellalloc = -1;
    point_charalloc = 0;
    ptr_charalloc = NULL;
    point_cellalloc = 0;
    ptr_cellalloc = NULL;
}
