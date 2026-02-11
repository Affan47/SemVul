mca_io_ompio_file_close (ompi_file_t *fh)
{
    int ret = OMPI_SUCCESS;
    mca_io_ompio_data_t *data;

    data = (mca_io_ompio_data_t *) fh->f_io_selected_data;
    if ( NULL == data ) {

	return ret;
    }
    ret = ompio_io_ompio_file_close(&data->ompio_fh);

    if ( NULL != data ) {
      free ( data );
    }

    return ret;
}
