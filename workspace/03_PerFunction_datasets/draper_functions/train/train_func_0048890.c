deviceDestroy(device_ *r)
{
	ReturnErrIf(r == NULL);
	Debug("Destroying Device %p", r);

	if(r->class != NULL) {
		if(r->class->unconfig != NULL) {
			ReturnErrIf(r->class->unconfig(r));
		}
	}

	if(r->pin != NULL)
		free(r->pin);

	if(r->private != NULL)
		free(r->private);

	if(r->refdes != NULL)
		free(r->refdes);

	free(r);

	return 0;
}
