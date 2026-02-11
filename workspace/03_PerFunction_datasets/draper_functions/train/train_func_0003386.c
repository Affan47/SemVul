elasticarray_resize(struct elasticarray * EA, size_t nrec, size_t reclen)
{


	if (nrec > SIZE_MAX / reclen) {
		errno = ENOMEM;
		goto err0;
	}


	if (resize(EA, nrec * reclen))
		goto err0;


	return (0);

err0:

	return (-1);
}
