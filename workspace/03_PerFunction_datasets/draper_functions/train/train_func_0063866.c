gauss_psdf_func(gdouble x,
                G_GNUC_UNUSED gint n_param,
                const gdouble *b,
                G_GNUC_UNUSED gpointer user_data,
                gboolean *fres)
{
    gdouble c;

    if (b[1] == 0) {
        *fres = FALSE;
        return 0;
    }
    *fres = TRUE;
    c = x*b[1];

    return b[0]*b[0]*b[1]/(2.0*GWY_SQRT_PI) * exp(-c*c/4);
}
