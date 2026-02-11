gwy_spectra_get_spectrum(GwySpectra *spectra, gint i)
{
    GwySpectrum *spec;

    g_return_val_if_fail(GWY_IS_SPECTRA(spectra), NULL);
    g_return_val_if_fail(i < spectra->spectra->len, NULL);

    spec = &g_array_index(spectra->spectra, GwySpectrum, i);

    return spec->ydata;
}
