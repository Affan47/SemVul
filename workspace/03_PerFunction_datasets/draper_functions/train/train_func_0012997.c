blk_rowxfer_mult(CS_BLKDESC * blkdesc, CS_INT * row_count)
{
	CS_INT rows_to_xfer = 0;
	CS_INT rows_xferred = 0;
	CS_RETCODE ret;

	tdsdump_log(TDS_DBG_FUNC, "blk_rowxfer_mult(%p, %p)\n", blkdesc, row_count);

	if (!row_count || *row_count == 0 )
		rows_to_xfer = blkdesc->bcpinfo.bind_count;
	else
		rows_to_xfer = *row_count;

	if (blkdesc->bcpinfo.direction == CS_BLK_IN) {
		ret = _blk_rowxfer_in(blkdesc, rows_to_xfer, &rows_xferred);
	} else {
		ret = _blk_rowxfer_out(blkdesc, rows_to_xfer, &rows_xferred);
	}
	if (row_count)
		*row_count = rows_xferred;
	return ret;

}
