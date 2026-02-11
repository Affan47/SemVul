fore200e_collect_rpd(struct fore200e* fore200e, struct rpd* rpd)
{
    struct host_bsq* bsq;
    struct buffer*   buffer;
    int              i;

    for (i = 0; i < rpd->nseg; i++) {


	buffer = FORE200E_HDL2BUF(rpd->rsd[ i ].handle);

	bsq = &fore200e->host_bsq[ buffer->scheme ][ buffer->magn ];

#ifdef FORE200E_BSQ_DEBUG
	bsq_audit(2, bsq, buffer->scheme, buffer->magn);

	if (buffer->supplied == 0)
	    printk(FORE200E "queue %d.%d, buffer %ld was not supplied\n",
		   buffer->scheme, buffer->magn, buffer->index);
	buffer->supplied = 0;
#endif


	buffer->next = bsq->freebuf;
	bsq->freebuf = buffer;


	bsq->freebuf_count++;
    }
}
