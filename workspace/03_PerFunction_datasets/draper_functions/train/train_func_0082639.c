row_extend_mirror(const gdouble *in, gdouble *out,
                  guint pos, guint width, guint res,
                  guint extend_left, guint extend_right,
                  G_GNUC_UNUSED gdouble value)
{
    guint res2 = 2*res, k0, j;
    gdouble *out2;
    row_extend_base(in, out, &pos, &width, res, &extend_left, &extend_right);

    out2 = out + extend_left + width;
    for (j = 0; j < extend_right; j++, out2++) {
        guint k = (pos + width + j) % res2;
        *out2 = (k < res) ? in[k] : in[res2-1 - k];
    }

    k0 = (extend_left/res2 + 1)*res2;
    out2 = out + extend_left-1;
    for (j = 1; j <= extend_left; j++, out2--) {
        guint k = (k0 + pos - j) % res2;
        *out2 = (k < res) ? in[k] : in[res2-1 - k];
    }
}
