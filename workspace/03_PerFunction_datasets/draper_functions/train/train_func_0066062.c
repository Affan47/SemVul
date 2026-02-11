ca_proplist_merge_ap(ca_proplist *p, va_list ap) {
        int ret;

        ca_return_val_if_fail(p, CA_ERROR_INVALID);

        for (;;) {
                const char *key, *value;

                if (!(key = va_arg(ap, const char*)))
                        break;

                if (!(value = va_arg(ap, const char*)))
                        return CA_ERROR_INVALID;

                if ((ret = ca_proplist_sets(p, key, value)) < 0)
                        return ret;
        }

        return CA_SUCCESS;
}
