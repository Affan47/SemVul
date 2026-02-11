endElement(void *userdata, const char *element) {
	parsedata *pdata = (parsedata *) userdata;
	endElementControl(pdata, element);
	if (pdata->prop->verbose) {
		int i;
		if (!strcmp(element, "name")) {
			printf("%s\n", pdata->databuf);
		}
		for (i = 0; i < pdata->depth; i++)
			printf("  ");
		printf("</%s>\n", pdata->current->name);
	}
	free(pdata->current->name);
	free(pdata->current);
	pdata->current = pdata->parent;
	pdata->parent = pdata->parent->parentptr;
	pdata->depth--;
}
