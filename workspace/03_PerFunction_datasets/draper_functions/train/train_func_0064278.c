krb5_mcc_store(krb5_context ctx, krb5_ccache id, krb5_creds *creds)
{
    krb5_error_code err;
    krb5_mcc_link *new_node;
    krb5_mcc_data *mptr = (krb5_mcc_data *)id->data;

    new_node = malloc(sizeof(krb5_mcc_link));
    if (new_node == NULL)
        return ENOMEM;
    err = krb5_copy_creds(ctx, creds, &new_node->creds);
    if (err)
        goto cleanup;
    k5_cc_mutex_lock(ctx, &mptr->lock);
    new_node->next = mptr->link;
    mptr->link = new_node;
    update_mcc_change_time(mptr);
    k5_cc_mutex_unlock(ctx, &mptr->lock);
    return 0;
cleanup:
    free(new_node);
    return err;
}
