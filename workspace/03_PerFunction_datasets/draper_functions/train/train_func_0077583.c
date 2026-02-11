text_array_delete(struct text_array *t)
{
	int n = t->width * t->height;
	int i;
	for(i = 0; i < n; i++) {
		if(t->data[i])
			free(t->data[i]);
	}
	free(t->data);
	free(t);
}
