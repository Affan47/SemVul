secmem_free( void *a )
{
    MEMBLOCK *mb;
    size_t size;

    if( !a )
	return;

    mb = (MEMBLOCK*)((char*)a - ((size_t) &((MEMBLOCK*)0)->u.aligned.c));
    size = mb->size;


    wipememory2(mb, 0xff, size );
    wipememory2(mb, 0xaa, size );
    wipememory2(mb, 0x55, size );
    wipememory2(mb, 0x00, size );
    mb->size = size;
    mb->u.next = unused_blocks;
    unused_blocks = mb;
    cur_blocks--;
    cur_alloced -= size;
}
