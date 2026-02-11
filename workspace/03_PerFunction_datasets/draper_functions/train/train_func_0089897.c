krb5_cc_register(krb5_context context, const krb5_cc_ops *ops,
                 krb5_boolean override)
{
    struct krb5_cc_typelist *t;

    k5_mutex_lock(&cc_typelist_lock);
    for (t = cc_typehead;t && strcmp(t->ops->prefix,ops->prefix);t = t->next)
        ;
    if (t) {
        if (override) {
            t->ops = ops;
            k5_mutex_unlock(&cc_typelist_lock);
            return 0;
        } else {
            k5_mutex_unlock(&cc_typelist_lock);
            return KRB5_CC_TYPE_EXISTS;
        }
    }
    if (!(t = (struct krb5_cc_typelist *) malloc(sizeof(*t)))) {
        k5_mutex_unlock(&cc_typelist_lock);
        return ENOMEM;
    }
    t->next = cc_typehead;
    t->ops = ops;
    cc_typehead = t;
    k5_mutex_unlock(&cc_typelist_lock);
    return 0;
}
