file_query(struct ompi_file_t *file,
           struct mca_io_base_file_t **private_data,
           int *priority)
{
    mca_io_ompio_data_t *data;

    *priority = priority_param;


    data = malloc(sizeof(mca_io_ompio_data_t));
    if (NULL == data) {
        return NULL;
    }

    *private_data = (struct mca_io_base_file_t*) data;


    return &mca_io_ompio_module;
}
