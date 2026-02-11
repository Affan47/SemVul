_gcry_mpi_get_opaque (gcry_mpi_t a, unsigned int *nbits)
{
    if( !(a->flags & 4) )
	log_bug("mpi_get_opaque on normal mpi\n");
    if( nbits )
	*nbits = a->sign;
    return a->d;
}
