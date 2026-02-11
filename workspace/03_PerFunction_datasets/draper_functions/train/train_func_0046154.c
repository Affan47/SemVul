mca_sharedfp_individual_iwrite(mca_io_ompio_file_t *fh,
                                   void *buf,
                                   int count,
                                   ompi_datatype_t *datatype,
                                   MPI_Request * request)
{
    int ret = OMPI_SUCCESS;
    size_t numofbytes = 0;
    OMPI_MPI_OFFSET_TYPE totalbytes = 0;
    mca_sharedfp_individual_header_record *headnode = NULL;
    struct mca_sharedfp_base_data_t *sh = NULL;
    mca_sharedfp_base_module_t * shared_fp_base_module = NULL;

    if(fh->f_sharedfp_data==NULL){
	if ( mca_sharedfp_individual_verbose ) {
	    printf("mca_sharedfp_individual_iwrite: opening the shared file pointer\n");
	}
        shared_fp_base_module = fh->f_sharedfp;

        ret = shared_fp_base_module->sharedfp_file_open(fh->f_comm,
                                                        fh->f_filename,
                                                        fh->f_amode,
                                                        fh->f_info,
                                                        fh);
        if (ret != OMPI_SUCCESS) {
            opal_output(1,"mca_sharedfp_individual_iwrite - error opening the shared file pointer\n");
            return ret;
        }
    }


    opal_datatype_type_size ( &datatype->super, &numofbytes);
    totalbytes = count * numofbytes;

    sh = fh->f_sharedfp_data;

    headnode = (mca_sharedfp_individual_header_record*)sh->selected_module_data;
    if ( NULL == headnode)  {
	opal_output (1, "sharedfp_individual_iwrite: headnode is NULL but file is open\n");
	return OMPI_ERROR;
    }


    ret = mca_sharedfp_individual_insert_metadata(OMPI_FILE_WRITE_SHARED,totalbytes,sh);


    ret = ompio_io_ompio_file_iwrite_at ( headnode->datafilehandle, headnode->datafile_offset,
					  buf, count, datatype, request);
    if ( OMPI_SUCCESS != ret )  {
	opal_output(1,"sharedfp_individual_iwrite: Error while iwriting the datafile \n");
	return ret;
    }


    headnode->datafile_offset = headnode->datafile_offset + totalbytes;

    return ret;
}
