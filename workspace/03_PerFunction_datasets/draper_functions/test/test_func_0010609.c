fore200e_alloc_rx_buf(struct fore200e *fore200e)
{
    int scheme, magn, nbr, size, i;

    struct host_bsq* bsq;
    struct buffer*   buffer;

    for (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) {
	for (magn = 0; magn < BUFFER_MAGN_NBR; magn++) {

	    bsq = &fore200e->host_bsq[ scheme ][ magn ];

	    nbr  = fore200e_rx_buf_nbr[ scheme ][ magn ];
	    size = fore200e_rx_buf_size[ scheme ][ magn ];

	    DPRINTK(2, "rx buffers %d / %d are being allocated\n", scheme, magn);


	    buffer = bsq->buffer = kzalloc(nbr * sizeof(struct buffer), GFP_KERNEL);

	    if (buffer == NULL)
		return -ENOMEM;

	    bsq->freebuf = NULL;

	    for (i = 0; i < nbr; i++) {

		buffer[ i ].scheme = scheme;
		buffer[ i ].magn   = magn;
#ifdef FORE200E_BSQ_DEBUG
		buffer[ i ].index  = i;
		buffer[ i ].supplied = 0;
#endif


		if (fore200e_chunk_alloc(fore200e,
					 &buffer[ i ].data, size, fore200e->bus->buffer_alignment,
					 DMA_FROM_DEVICE) < 0) {

		    while (i > 0)
			fore200e_chunk_free(fore200e, &buffer[ --i ].data);
		    kfree(buffer);

		    return -ENOMEM;
		}


		buffer[ i ].next = bsq->freebuf;
		bsq->freebuf = &buffer[ i ];
	    }

	    bsq->freebuf_count = nbr;

#ifdef FORE200E_BSQ_DEBUG
	    bsq_audit(3, bsq, scheme, magn);
#endif
	}
    }

    fore200e->state = FORE200E_STATE_ALLOC_BUF;
    return 0;
}
