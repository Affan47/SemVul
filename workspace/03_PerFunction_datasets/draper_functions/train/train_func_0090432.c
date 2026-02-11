alloc_memblock ( size_t size, size_t align, size_t offset ) {
	struct memory_block *block;
	size_t align_mask;
	size_t pre_size;
	ssize_t post_size;
	struct memory_block *pre;
	struct memory_block *post;
	struct memory_block *ptr;

	valgrind_make_blocks_defined();


	size = ( size + MIN_MEMBLOCK_SIZE - 1 ) & ~( MIN_MEMBLOCK_SIZE - 1 );
	align_mask = ( align - 1 ) | ( MIN_MEMBLOCK_SIZE - 1 );

	DBG ( "Allocating %#zx (aligned %#zx+%zx)\n", size, align, offset );
	while ( 1 ) {

		list_for_each_entry ( block, &free_blocks, list ) {
			pre_size = ( ( offset - virt_to_phys ( block ) )
				     & align_mask );
			post_size = ( block->size - pre_size - size );
			if ( post_size >= 0 ) {


				pre   = block;
				block = ( ( ( void * ) pre   ) + pre_size );
				post  = ( ( ( void * ) block ) + size     );
				DBG ( "[%p,%p) -> [%p,%p) + [%p,%p)\n", pre,
				      ( ( ( void * ) pre ) + pre->size ),
				      pre, block, post,
				      ( ( ( void * ) pre ) + pre->size ) );


				if ( (size_t) post_size >= MIN_MEMBLOCK_SIZE ) {
					VALGRIND_MAKE_MEM_DEFINED ( post,
							     sizeof ( *post ) );
					post->size = post_size;
					list_add ( &post->list, &pre->list );
				}


				pre->size = pre_size;


				if ( pre_size < MIN_MEMBLOCK_SIZE )
					list_del ( &pre->list );

				freemem -= size;

				DBG ( "Allocated [%p,%p)\n", block,
				      ( ( ( void * ) block ) + size ) );
				ptr = block;
				goto done;
			}
		}


		if ( ! discard_cache() ) {

			DBG ( "Failed to allocate %#zx (aligned %#zx)\n",
			      size, align );
			ptr = NULL;
			goto done;
		}
	}

 done:
	valgrind_make_blocks_noaccess();
	return ptr;
}
