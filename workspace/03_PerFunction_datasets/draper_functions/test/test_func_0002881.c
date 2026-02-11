cr_utils_utf8_str_to_ucs1 (const guchar * a_in,
                           gulong * a_in_len,
                           guchar ** a_out, gulong * a_out_len)
{
        enum CRStatus status = CR_OK;

        g_return_val_if_fail (a_in && a_in_len
                              && a_out && a_out_len, CR_BAD_PARAM_ERROR);

        if (*a_in_len < 1) {
                *a_out_len = 0;
                *a_out = NULL;
                return CR_OK;
        }

        status = cr_utils_utf8_str_len_as_ucs4 (a_in, &a_in[*a_in_len - 1],
                                                a_out_len);

        g_return_val_if_fail (status == CR_OK, status);

        *a_out = (guchar *) g_malloc0 (*a_out_len * sizeof (guint32));

        status = cr_utils_utf8_to_ucs1 (a_in, a_in_len, *a_out, a_out_len);
        return status;
}
