free_iob ( struct io_buffer *iobuf ) {
	if ( iobuf ) {
		assert ( iobuf->head <= iobuf->data );
		assert ( iobuf->data <= iobuf->tail );
		assert ( iobuf->tail <= iobuf->end );
		free_dma ( iobuf->head,
			   ( iobuf->end - iobuf->head ) + sizeof ( *iobuf ) );
	}
}
