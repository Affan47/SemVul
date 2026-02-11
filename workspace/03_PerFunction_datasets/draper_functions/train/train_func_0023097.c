schema_copy_extensions(schemaext *extensions)
{
    schemaext *ext = NULL, *head = NULL;
    while(extensions){
        schemaext *newext = (schemaext *)slapi_ch_calloc(1, sizeof(schemaext));
        newext->term = slapi_ch_strdup(extensions->term);
        newext->values = charray_dup(extensions->values);
        newext->value_count = extensions->value_count;
        if(ext == NULL){
            ext = newext;
            head = newext;
        } else {
            ext->next = newext;
            ext = newext;
        }
        extensions = extensions->next;
    }

    return head;
}
