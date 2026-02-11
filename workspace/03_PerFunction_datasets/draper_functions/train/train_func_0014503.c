varray_assign(VARRAY *vb, int index, int force)
{
	if (index < 0)
		die("varray_assign: illegal index value.");
	if (index >= vb->length) {
		if (force)
			vb->length = index + 1;
		else if (index == 0 && vb->length == 0)
			return NULL;
		else
			die("varray_assign: index(=%d) is out of range.", index);
	}


	if (index >= vb->alloced) {
		int old_alloced = vb->alloced;

		while (index >= vb->alloced)
			vb->alloced += vb->expand;


		if (vb->vbuf == NULL)
			vb->vbuf = (char *)check_malloc(vb->size * vb->alloced);
		else
			vb->vbuf = (char *)check_realloc(vb->vbuf, vb->size * vb->alloced);
		if (debug)
			fprintf(stderr, "Expanded: from %d to %d.\n", old_alloced, vb->alloced);
	}
	return (void *)(vb->vbuf + vb->size * index);
}
