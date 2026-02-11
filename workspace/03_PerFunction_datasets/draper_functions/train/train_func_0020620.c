orte_iof_base_open(mca_base_open_flag_t flags)
{
    int rc, xmlfd;


    if (0 > orte_iof_base.output_limit) {
        orte_iof_base.output_limit = INT_MAX;
    }


    if (NULL != orte_output_filename) {


        char *path;
        path = opal_dirname(orte_output_filename);
        if (0 != strcmp(path, orte_output_filename)) {


            if (ORTE_SUCCESS != (rc = opal_os_dirpath_create(path, S_IRWXU))) {
                return rc;
            }
        }
    }


    if (!ORTE_PROC_IS_DAEMON ||
        (ORTE_PROC_IS_DAEMON && ORTE_PROC_IS_CM)) {
        if (orte_xml_output) {
            if (NULL != orte_xml_fp) {

                xmlfd = fileno(orte_xml_fp);
            } else {
                xmlfd = 1;
            }

            ORTE_IOF_SINK_DEFINE(&orte_iof_base.iof_write_stdout, ORTE_PROC_MY_NAME,
                                 xmlfd, ORTE_IOF_STDOUT, orte_iof_base_write_handler, NULL);


        } else {

            ORTE_IOF_SINK_DEFINE(&orte_iof_base.iof_write_stdout, ORTE_PROC_MY_NAME,
                                 1, ORTE_IOF_STDOUT, orte_iof_base_write_handler, NULL);

            ORTE_IOF_SINK_DEFINE(&orte_iof_base.iof_write_stderr, ORTE_PROC_MY_NAME,
                                 2, ORTE_IOF_STDERR, orte_iof_base_write_handler, NULL);
        }


    }


    return mca_base_framework_components_open(&orte_iof_base_framework, flags);
}
