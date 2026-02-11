_dxfinmem(Pointer x)
{
    int i;

    for (i=0; i<alloc_chunks; i++)
        if ((x >= alloc_addr_start[i]) && (x < alloc_addr_end[i]))
	    return 1;

    return 0;
}
