H5E_walk2_cb(unsigned n, const H5E_error2_t *err_desc, void *client_data)
{
    H5E_print_t         *eprint  = (H5E_print_t *)client_data;
    FILE		*stream;
    H5E_cls_t           *cls_ptr;
    H5E_msg_t           *maj_ptr;
    H5E_msg_t           *min_ptr;
    const char		*maj_str = "No major description";
    const char		*min_str = "No minor description";
    unsigned            have_desc = 1;
    herr_t              ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(err_desc);


    if(!client_data)
        stream = stderr;
    else
        stream = eprint->stream;


    maj_ptr = (H5E_msg_t *)H5I_object_verify(err_desc->maj_num, H5I_ERROR_MSG);
    min_ptr = (H5E_msg_t *)H5I_object_verify(err_desc->min_num, H5I_ERROR_MSG);


    if(!maj_ptr || !min_ptr)
        HGOTO_DONE(FAIL)

    if(maj_ptr->msg)
        maj_str = maj_ptr->msg;
    if(min_ptr->msg)
        min_str = min_ptr->msg;


    cls_ptr = (H5E_cls_t *)H5I_object_verify(err_desc->cls_id, H5I_ERROR_CLASS);


    if(!cls_ptr)
        HGOTO_DONE(FAIL)


    if(eprint->cls.lib_name == NULL || HDstrcmp(cls_ptr->lib_name, eprint->cls.lib_name)) {

        if(cls_ptr->cls_name)
            eprint->cls.cls_name = cls_ptr->cls_name;
        if(cls_ptr->lib_name)
            eprint->cls.lib_name = cls_ptr->lib_name;
        if(cls_ptr->lib_vers)
            eprint->cls.lib_vers = cls_ptr->lib_vers;

        fprintf(stream, "%s-DIAG: Error detected in %s (%s) ",
            (cls_ptr->cls_name ? cls_ptr->cls_name : "(null)"),
            (cls_ptr->lib_name ? cls_ptr->lib_name : "(null)"),
            (cls_ptr->lib_vers ? cls_ptr->lib_vers : "(null)"));


#ifdef H5_HAVE_PARALLEL
        {
            int mpi_rank, mpi_initialized;

	    MPI_Initialized(&mpi_initialized);
	    if(mpi_initialized) {
	        MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	        fprintf(stream, "MPI-process %d", mpi_rank);
	    }
            else
	        fprintf(stream, "thread 0");
        }
#elif defined(H5_HAVE_THREADSAFE)
        fprintf(stream, "thread %lu", (unsigned long)HDpthread_self_ulong());
#else
        fprintf(stream, "thread 0");
#endif
        fprintf(stream, ":\n");
    }


    if(err_desc->desc == NULL || HDstrlen(err_desc->desc) == 0)
        have_desc = 0;


    fprintf(stream, "%*s#%03u: %s line %u in %s()%s%s\n",
	     H5E_INDENT, "", n, err_desc->file_name, err_desc->line,
	     err_desc->func_name, (have_desc ? ": " : ""),
             (have_desc ? err_desc->desc : ""));
    fprintf(stream, "%*smajor: %s\n", (H5E_INDENT * 2), "", maj_str);
    fprintf(stream, "%*sminor: %s\n", (H5E_INDENT * 2), "", min_str);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
