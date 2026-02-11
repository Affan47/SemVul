mca_io_ompio_generate_current_file_view (ompi_file_t *fp,
					     size_t max_data,
					     struct iovec **f_iov,
					     int *iov_count)
{
    int res;
    mca_io_ompio_data_t *data;
    mca_io_ompio_file_t *fh;

    data = (mca_io_ompio_data_t *) fp->f_io_selected_data;
    fh = &data->ompio_fh;
    res = ompi_io_ompio_generate_current_file_view (fh,
						    max_data,
						    f_iov,
						    iov_count);
    if(res != OMPI_SUCCESS){
	printf("Error in ompi_io_generate_current_file_view\n");
	return res;
    }

    return OMPI_SUCCESS;
}
