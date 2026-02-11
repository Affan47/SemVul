update_max(struct Max *m, int n, double k)
{
    if (k > m->val) {
	m->idx = n;
	m->val = k;
    }
}
