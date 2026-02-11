ambig_check(struct info *info, struct fa *fa1, struct fa *fa2,
            enum lens_type typ,  struct lens *l1, struct lens *l2,
            const char *msg, bool iterated) {
    char *upv, *pv, *v;
    size_t upv_len;
    struct value *exn = NULL;
    int r;

    r = fa_ambig_example(fa1, fa2, &upv, &upv_len, &pv, &v);
    if (r < 0) {
        exn = make_exn_value(ref(info), "not enough memory");
        if (exn != NULL) {
            return exn;
        } else {
            ERR_REPORT(info, AUG_ENOMEM, NULL);
            return info->error->exn;
        }
    }

    if (upv != NULL) {
        char *e_u, *e_up, *e_upv, *e_pv, *e_v;
        char *s1, *s2;

        if (typ == ATYPE) {
            e_u = enc_format(upv, pv - upv);
            e_up = enc_format(upv, v - upv);
            e_upv = enc_format(upv, upv_len);
            e_pv = enc_format(pv, strlen(pv));
            e_v = enc_format(v, strlen(v));
            lns_format_atype(l1, &s1);
            lns_format_atype(l2, &s2);
        } else {
            e_u = escape(upv, pv - upv, RX_ESCAPES);
            e_up = escape(upv, v - upv, RX_ESCAPES);
            e_upv = escape(upv, -1, RX_ESCAPES);
            e_pv = escape(pv, -1, RX_ESCAPES);
            e_v = escape(v, -1, RX_ESCAPES);
            s1 = regexp_escape(ltype(l1, typ));
            s2 = regexp_escape(ltype(l2, typ));
        }
        exn = make_exn_value(ref(info), "%s", msg);
        if (iterated) {
            exn_printf_line(exn, "  Iterated regexp: /%s/", s1);
        } else {
            exn_printf_line(exn, "  First regexp: /%s/", s1);
            exn_printf_line(exn, "  Second regexp: /%s/", s2);
        }
        exn_printf_line(exn, "  '%s' can be split into", e_upv);
        exn_printf_line(exn, "  '%s|=|%s'\n", e_u, e_pv);
        exn_printf_line(exn, " and");
        exn_printf_line(exn, "  '%s|=|%s'\n", e_up, e_v);
        free(e_u);
        free(e_up);
        free(e_upv);
        free(e_pv);
        free(e_v);
        free(s1);
        free(s2);
    }
    free(upv);
    return exn;
}
