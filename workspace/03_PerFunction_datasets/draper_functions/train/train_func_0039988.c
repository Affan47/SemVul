gwy_spectra_itoxy(GwySpectra *spectra,
                  guint i,
                  gdouble *x,
                  gdouble *y)
{
    GwySpectrum *spec;

    g_return_if_fail(GWY_IS_SPECTRA(spectra));
    g_return_if_fail(i < spectra->spectra->len);

    spec = &g_array_index(spectra->spectra, GwySpectrum, i);
    if (x)
        *x = spec->x;
    if (y)
        *y = spec->y;
}
