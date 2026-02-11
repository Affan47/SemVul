krb5_fcc_skip_header(krb5_context context, krb5_ccache id)
{
    krb5_fcc_data *data = (krb5_fcc_data *)id->data;
    krb5_error_code kret;
    krb5_ui_2 fcc_flen;

    k5_cc_mutex_assert_locked(context, &((krb5_fcc_data *) id->data)->lock);

    fcc_lseek(data, (off_t) sizeof(krb5_ui_2), SEEK_SET);
    if (data->version == KRB5_FCC_FVNO_4) {
        kret = krb5_fcc_read_ui_2(context, id, &fcc_flen);
        if (kret) return kret;
        if(fcc_lseek(data, (off_t) fcc_flen, SEEK_CUR) < 0)
            return errno;
    }
    return KRB5_OK;
}
