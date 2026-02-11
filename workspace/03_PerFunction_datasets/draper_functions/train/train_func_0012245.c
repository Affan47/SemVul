krb5_mcc_destroy(krb5_context context, krb5_ccache id)
{
    krb5_mcc_list_node **curr, *node;
    krb5_mcc_data *d;

    k5_cc_mutex_lock(context, &krb5int_mcc_mutex);

    d = (krb5_mcc_data *)id->data;
    for (curr = &mcc_head; *curr; curr = &(*curr)->next) {
        if ((*curr)->cache == d) {
            node = *curr;
            *curr = node->next;
            free(node);
            break;
        }
    }
    k5_cc_mutex_unlock(context, &krb5int_mcc_mutex);

    k5_cc_mutex_lock(context, &d->lock);

    krb5_mcc_free(context, id);
    free(d->name);
    k5_cc_mutex_unlock(context, &d->lock);
    k5_cc_mutex_destroy(&d->lock);
    free(d);
    free(id);

    krb5_change_cache ();
    return KRB5_OK;
}
