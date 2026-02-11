mmc_mode_sense(CdIo_t *p_cdio,  void *p_buf, unsigned int i_size,
	       int page)
{


    if ( DRIVER_OP_SUCCESS == mmc_mode_sense_6(p_cdio, p_buf, i_size, page) )
	return DRIVER_OP_SUCCESS;
    return mmc_mode_sense_10(p_cdio, p_buf, i_size, page);
}
