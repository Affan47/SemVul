Write (writer_t *wr, const void *data, Addr_t nbytes)
{
    wr_buffer_t	*bp = BufOf(wr);

    if (wr->errFlg)
	return;

    ASSERT(bp->next+nbytes <= bp->top);

    memcpy (bp->next, data, nbytes);
    bp->next += nbytes;

}
