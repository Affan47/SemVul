compare_pairs_x (const void *a, const void *b)
{
    const struct xy_pair *pa = a;
    const struct xy_pair *pb = b;
    int ret;

    ret = (pa->x > pb->x) - (pa->x < pb->x);
    if (ret == 0) {
	ret = (pa->y > pb->y) - (pa->y < pb->y);
    }

    return ret;
}
