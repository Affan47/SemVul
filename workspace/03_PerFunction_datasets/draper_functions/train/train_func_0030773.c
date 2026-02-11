schema_free_extensions(schemaext *extensions)
{
    if(extensions){
        schemaext *prev;

        while(extensions){
            slapi_ch_free_string(&extensions->term);
            charray_free(extensions->values);
            prev = extensions;
            extensions = extensions->next;
            slapi_ch_free( (void **)&prev);
        }
    }
}
