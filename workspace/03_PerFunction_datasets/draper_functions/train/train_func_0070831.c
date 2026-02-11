log_block_checksum_is_ok_or_old_format(

	const byte*	block)
{
#ifdef UNIV_LOG_DEBUG
	return(TRUE);
#endif
	if (log_block_calc_checksum(block) == log_block_get_checksum(block)) {

		return(TRUE);
	}

	if (log_block_get_hdr_no(block) == log_block_get_checksum(block)) {


#if 0
		fprintf(stderr,
			"InnoDB: Scanned old format < InnoDB-3.23.52"
			" log block number %lu\n",
			log_block_get_hdr_no(block));
#endif
		return(TRUE);
	}

	return(FALSE);
}
