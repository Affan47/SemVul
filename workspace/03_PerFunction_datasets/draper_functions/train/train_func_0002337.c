find_among_b(struct SN_env * z, struct among * v, int v_size) {

    int i = 0;
    int j = v_size;

    int c = z->c; int lb = z->lb;
    symbol * q = z->p + c - 1;

    struct among * w;

    int common_i = 0;
    int common_j = 0;

    int first_key_inspected = 0;

    while(1) {
	int k = i + ((j - i) >> 1);
	int diff = 0;
	int common = common_i < common_j ? common_i : common_j;
	w = v + k;
	{
	    int i; for (i = w->s_size - 1 - common; i >= 0; i--) {
		if (c - common == lb) { diff = -1; break; }
		diff = q[- common] - w->s[i];
		if (diff != 0) break;
		common++;
	    }
	}
	if (diff < 0) { j = k; common_j = common; }
		 else { i = k; common_i = common; }
	if (j - i <= 1) {
	    if (i > 0) break;
	    if (j == i) break;
	    if (first_key_inspected) break;
	    first_key_inspected = 1;
	}
    }
    while(1) {
	w = v + i;
	if (common_i >= w->s_size) {
	    z->c = c - w->s_size;
	    if (w->function == 0) return w->result;
	    {
		int res = w->function(z);
		z->c = c - w->s_size;
		if (res) return w->result;
	    }
	}
	i = w->substring_i;
	if (i < 0) return 0;
    }
}
