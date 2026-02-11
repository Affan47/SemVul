get_min_d(void *v1, void *v2)
{
    void *rc;

    rc = v2;
    if (*(DCELL *) v1 < *(DCELL *) v2)
	rc = v1;
    return rc;
}
