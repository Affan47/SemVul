Cover(DocRepresentation *doc, int len, QueryRepresentation *qr, Extention *ext)
{
	DocRepresentation *ptr;
	int			lastpos = ext->pos;
	int			i;
	bool		found = false;


	check_stack_depth();

	memset(qr->operandexist, 0, sizeof(bool) * qr->query->size);

	ext->p = 0x7fffffff;
	ext->q = 0;
	ptr = doc + ext->pos;


	while (ptr - doc < len)
	{
		for (i = 0; i < ptr->nitem; i++)
		{
			if (ptr->item[i]->type == QI_VAL)
				QR_SET_OPERAND_EXISTS(qr, ptr->item[i]);
		}
		if (TS_execute(GETQUERY(qr->query), (void *) qr, false, checkcondition_QueryOperand))
		{
			if (ptr->pos > ext->q)
			{
				ext->q = ptr->pos;
				ext->end = ptr;
				lastpos = ptr - doc;
				found = true;
			}
			break;
		}
		ptr++;
	}

	if (!found)
		return false;

	memset(qr->operandexist, 0, sizeof(bool) * qr->query->size);

	ptr = doc + lastpos;


	while (ptr >= doc + ext->pos)
	{
		for (i = 0; i < ptr->nitem; i++)
			if (ptr->item[i]->type == QI_VAL)
				QR_SET_OPERAND_EXISTS(qr, ptr->item[i]);
		if (TS_execute(GETQUERY(qr->query), (void *) qr, true, checkcondition_QueryOperand))
		{
			if (ptr->pos < ext->p)
			{
				ext->begin = ptr;
				ext->p = ptr->pos;
			}
			break;
		}
		ptr--;
	}

	if (ext->p <= ext->q)
	{


		ext->pos = (ptr - doc) + 1;
		return true;
	}

	ext->pos++;
	return Cover(doc, len, qr, ext);
}
