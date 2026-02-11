krb5_free_last_req(krb5_context context, krb5_last_req_entry **val)
{
    register krb5_last_req_entry **temp;

    if (val == NULL)
        return;
    for (temp = val; *temp; temp++)
        free(*temp);
    free(val);
}
