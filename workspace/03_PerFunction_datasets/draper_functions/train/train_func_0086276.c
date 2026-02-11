fixquota_addroot(struct quota *q,
			    void *rock __attribute__((unused)))
{
    if (quota_num == quota_alloc) {

	quota_alloc += QUOTAGROW;
	quota = (struct quotaentry *)
	    xrealloc((char *)quota, quota_alloc * sizeof(struct quotaentry));
	memset(&quota[quota_num], 0, QUOTAGROW * sizeof(struct quotaentry));
    }


    quota[quota_num].allocname   = xstrdup(q->root);
    quota[quota_num].quota.root  = quota[quota_num].allocname;
    quota[quota_num].quota.limit = q->limit;
    quota[quota_num].quota.used  = q->used;
    quota_num++;

    return 0;
}
