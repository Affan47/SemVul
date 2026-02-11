CopyResult(RESULT ** result, RESULT * value)
{
    if (*result == NULL) {
	if ((*result = NewResult()) == NULL)
	    return NULL;
    }

    (*result)->type = value->type;
    (*result)->number = value->number;

    if (value->string == NULL) {
	(*result)->size = 0;
	if ((*result)->string)
	    free((*result)->string);
	(*result)->string = NULL;
    } else {

	if ((*result)->string == NULL || value->size > (*result)->size) {
	    if ((*result)->string)
		free((*result)->string);
	    (*result)->size = value->size;
	    (*result)->string = malloc((*result)->size);
	}
	strcpy((*result)->string, value->string);
    }
    return *result;
}
