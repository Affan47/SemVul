free_keywords(vector keywords)
{
	struct keyword *keyword;
	int i;

	if (!keywords)
		return;

	for (i = 0; i < VECTOR_SIZE(keywords); i++) {
		keyword = VECTOR_SLOT(keywords, i);
		if (keyword->sub)
			free_keywords(keyword->sub);
		FREE(keyword);
	}
	vector_free(keywords);
}
