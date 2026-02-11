parse_port_name(const char *port_name,
                           char **hnp_uri,
                           char **rml_uri,
                           orte_rml_tag_t *ptag)
{
    char *tmpstring=NULL, *ptr;
    int tag;
    int rc;


    tmpstring = strdup(port_name);


    if (NULL == (ptr = strrchr(tmpstring, ':'))) {
        rc = OMPI_ERR_NOT_FOUND;
        goto cleanup;
    }


    *ptr = '\0';
    ptr++;


    sscanf(ptr,"%d", &tag);


    if (NULL == (ptr = strchr(tmpstring, '+'))) {
        rc = OMPI_ERR_NOT_FOUND;
        goto cleanup;
    }
    *ptr = '\0';
    ptr++;


    if(NULL != hnp_uri) *hnp_uri = tmpstring;
    else free(tmpstring);
    if(NULL != rml_uri) *rml_uri = strdup(ptr);
    if(NULL != ptag) *ptag = tag;

    return OMPI_SUCCESS;

cleanup:

    if (NULL != tmpstring) {
        free(tmpstring);
    }
    return rc;
}
