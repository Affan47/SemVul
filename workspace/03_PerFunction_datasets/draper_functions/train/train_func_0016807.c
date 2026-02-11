zFreeGTFVec (zGTFVec *vec) {
	int i;
	for (i = 0; i < vec->size; ++i) {
		zFreeGTFfeature(&vec->elem[i]);
	}
	zFree(vec->elem);
	vec->elem  = NULL;
	vec->size  = 0;
	vec->limit = 0;
	vec->last  = NULL;
}
