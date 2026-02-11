createwbmp(int width, int height, int color)
{
	int i;
	Wbmp *wbmp;

	if((wbmp = (Wbmp *)gdMalloc(sizeof (Wbmp))) == NULL) {
		return (NULL);
	}

	if(overflow2(sizeof(int), width)) {
		gdFree(wbmp);
		return NULL;
	}

	if(overflow2(sizeof(int) * width, height)) {
		gdFree(wbmp);
		return NULL;
	}

	if((wbmp->bitmap = (int *)gdMalloc(sizeof(int) * width * height)) == NULL) {
		gdFree(wbmp);
		return NULL;
	}

	wbmp->width = width;
	wbmp->height = height;

	for(i = 0; i < width * height; wbmp->bitmap[i++] = color);

	return wbmp;
}
