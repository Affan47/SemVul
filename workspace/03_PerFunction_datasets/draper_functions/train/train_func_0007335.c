rb_io_fptr_cleanup(rb_io_t *fptr, int noraise)
{
    if (fptr->finalize) {
	(*fptr->finalize)(fptr, noraise);
    }
    else {
	fptr_finalize(fptr, noraise);
    }
}
