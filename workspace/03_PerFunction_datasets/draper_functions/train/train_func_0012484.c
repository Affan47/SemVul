_hx509_AlgorithmIdentifier_cmp(const AlgorithmIdentifier *p,
			       const AlgorithmIdentifier *q)
{
    int diff;
    diff = der_heim_oid_cmp(&p->algorithm, &q->algorithm);
    if (diff)
	return diff;
    if (p->parameters) {
	if (q->parameters)
	    return heim_any_cmp(p->parameters,
				q->parameters);
	else
	    return 1;
    } else {
	if (q->parameters)
	    return -1;
	else
	    return 0;
    }
}
