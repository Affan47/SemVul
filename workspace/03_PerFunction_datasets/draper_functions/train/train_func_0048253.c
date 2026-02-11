gwy_spectra_remove_spectrum(GwySpectra *spectra,
                            guint i)
{
    GwySpectrum *spec;

    g_return_if_fail(GWY_IS_SPECTRA(spectra));
    g_return_if_fail(i < spectra->spectra->len);

    spec = &g_array_index(spectra->spectra, GwySpectrum, i);
    g_object_unref(spec->ydata);

    g_array_remove_index(spectra->spectra, i);
}
