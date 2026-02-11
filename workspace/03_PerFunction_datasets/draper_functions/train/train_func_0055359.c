qccHunkAlloc(size_t mem)
{
	qccalloced+=mem;
	if (qccalloced > qcchunksize)
		QCC_Error(ERR_INTERNAL, "Compile hunk was filled");

	memset(qcchunk+qccalloced-mem, 0, mem);
	return qcchunk+qccalloced-mem;
}
