figptarray(GVJ_t *job, pointf * A, int n, int close)
{
    int i;
    point p;

    for (i = 0; i < n; i++) {
	PF2P(A[i],p);
        gvprintf(job, " %d %d", p.x, p.y);
    }
    if (close) {
	PF2P(A[0],p);
        gvprintf(job, " %d %d", p.x, p.y);
    }
    gvputs(job, "\n");
}
