mca_io_romio_file_sync (ompi_file_t *fh)
{
    int ret;
    mca_io_romio_data_t *data;

    data = (mca_io_romio_data_t *) fh->f_io_selected_data;
    OPAL_THREAD_LOCK (&mca_io_romio_mutex);
    ret = ROMIO_PREFIX(MPI_File_sync) (data->romio_fh);
    OPAL_THREAD_UNLOCK (&mca_io_romio_mutex);

    return ret;
}
