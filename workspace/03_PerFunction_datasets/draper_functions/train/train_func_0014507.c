file_destructor(ompi_file_t *file)
{


    switch (file->f_io_version) {
    case MCA_IO_BASE_V_2_0_0:
        file->f_io_selected_module.v2_0_0.io_module_file_close(file);
        break;
    default:

        break;
    }


    if (NULL != file->f_comm) {
        OBJ_RELEASE(file->f_comm);
#if OPAL_ENABLE_DEBUG
        file->f_comm = NULL;
#endif
    }

    if (NULL != file->f_filename) {
        free(file->f_filename);
#if OPAL_ENABLE_DEBUG
        file->f_filename = NULL;
#endif
    }

    if (NULL != file->error_handler) {
        OBJ_RELEASE(file->error_handler);
#if OPAL_ENABLE_DEBUG
        file->error_handler = NULL;
#endif
    }

    if (NULL != file->f_info) {
        OBJ_RELEASE(file->f_info);
#if OPAL_ENABLE_DEBUG
        file->f_info = NULL;
#endif
    }


    if (MPI_UNDEFINED != file->f_f_to_c_index &&
        NULL != opal_pointer_array_get_item(&ompi_file_f_to_c_table,
                                            file->f_f_to_c_index)) {
        opal_pointer_array_set_item(&ompi_file_f_to_c_table,
                                    file->f_f_to_c_index, NULL);
    }
}
