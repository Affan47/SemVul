PQbucket(struct Halfedge *he)
{
    int bucket;

    bucket = (he->ystar - ymin) / deltay * PQhashsize;
    if (bucket < 0)
	bucket = 0;
    if (bucket >= PQhashsize)
	bucket = PQhashsize - 1;
    if (bucket < PQmin)
	PQmin = bucket;
    return (bucket);
}
