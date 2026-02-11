fvector(
int nl,
int nh
)	{
	float *v;

	if ((v = (float *) malloc((nh-nl+1) * sizeof(float))) == NULL) {
		if (ret_null_on_malloc_fail)
			return NULL;
		else
			error("Malloc failure in fvector()");
	}
	return v-nl;
}
