dtdDestroy(DTD *p)
{
	HASH_TABLE_ITER iter;
	hashTableIterInit(&iter, &(p->elementTypes));
	for (;;) {
		ELEMENT_TYPE *e = (ELEMENT_TYPE *)hashTableIterNext(&iter);
		if (!e)
			break;
		if (e->allocDefaultAtts != 0)
			free(e->defaultAtts);
	}
	hashTableDestroy(&(p->generalEntities));
	hashTableDestroy(&(p->elementTypes));
	hashTableDestroy(&(p->attributeIds));
	hashTableDestroy(&(p->prefixes));
	poolDestroy(&(p->pool));
}
