ber_encode_krb5_key_data(krb5_key_data *data,
                             int numk, int mkvno,
                             struct berval **encoded)
{
    BerElement *be = NULL;
    ber_tag_t tag;
    int ret, i;

    be = ber_alloc_t(LBER_USE_DER);
    if (!be) {
        return ENOMEM;
    }

    tag = LBER_CONSTRUCTED | LBER_CLASS_CONTEXT;

    ret = ber_printf(be, "{t[i]t[i]t[i]t[i]t[{",
                         tag | 0, 1, tag | 1, 1,
                         tag | 2, (ber_int_t)data[0].key_data_kvno,
                         tag | 3, (ber_int_t)mkvno, tag | 4);
    if (ret == -1) {
        ret = EFAULT;
        goto done;
    }

    for (i = 0; i < numk; i++) {

        ret = ber_printf(be, "{");
        if (ret == -1) {
            ret = EFAULT;
            goto done;
        }

        if (data[i].key_data_length[1] != 0) {
            ret = ber_printf(be, "t[{t[i]",
                                 tag | 0,
                                   tag | 0,
                                     (ber_int_t)data[i].key_data_type[1]);
            if (ret != -1) {
                ret = ber_printf(be, "t[o]",
                                     tag | 1,
                                       data[i].key_data_contents[1],
                                       (ber_len_t)data[i].key_data_length[1]);
            }
            if (ret != -1) {
                ret = ber_printf(be, "}]");
            }
            if (ret == -1) {
                ret = EFAULT;
                goto done;
            }
        }

        ret = ber_printf(be, "t[{t[i]t[o]}]",
                              tag | 1,
                                tag | 0,
                                  (ber_int_t)data[i].key_data_type[0],
                                tag | 1,
                                  data[i].key_data_contents[0],
                                  (ber_len_t)data[i].key_data_length[0]);
        if (ret == -1) {
            ret = EFAULT;
            goto done;
        }

        ret = ber_printf(be, "}");
        if (ret == -1) {
            ret = EFAULT;
            goto done;
        }
    }

    ret = ber_printf(be, "}]}");
    if (ret == -1) {
        ret = EFAULT;
        goto done;
    }

    ret = ber_flatten(be, encoded);
    if (ret == -1) {
        ret = EFAULT;
        goto done;
    }

done:
    ber_free(be, 1);
    return ret;
}
