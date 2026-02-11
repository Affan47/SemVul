giraffe_rebinning_create(GiImage *spectra, GiImage *errors)
{

    GiRebinning *rebin = giraffe_rebinning_new();

    if (spectra) {
        rebin->spectra = spectra;
    }

    if (errors) {
        rebin->errors = errors;
    }

    return rebin;

}
