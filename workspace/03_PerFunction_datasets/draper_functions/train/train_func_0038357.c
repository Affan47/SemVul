row_extend_periodic(const gdouble *in, gdouble *out,
                    guint pos, guint width, guint res,
                    guint extend_left, guint extend_right,
                    G_GNUC_UNUSED gdouble value)
{
    guint k0, j;
    gdouble *out2;
    row_extend_base(in, out, &pos, &width, res, &extend_left, &extend_right);

    out2 = out + extend_left + width;
    for (j = 0; j < extend_right; j++, out2++) {
        guint k = (pos + width + j) % res;
        *out2 = in[k];
    }

    k0 = (extend_left/res + 1)*res;
    out2 = out + extend_left-1;
    for (j = 1; j <= extend_left; j++, out2--) {
        guint k = (k0 + pos - j) % res;
        *out2 = in[k];
    }
}
