compareQueryOperand(const void *a, const void *b, void *arg)
{
	char	   *operand = (char *) arg;
	QueryOperand *qa = (*(QueryOperand **) a);
	QueryOperand *qb = (*(QueryOperand **) b);

	if (qa->length == qb->length)
		return strncmp(operand + qa->distance,
					   operand + qb->distance,
					   qb->length);

	return (qa->length > qb->length) ? 1 : -1;
}
