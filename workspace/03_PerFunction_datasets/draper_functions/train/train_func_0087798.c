amdlibDisplayWavelength(amdlibWAVELENGTH *wavelength)
{
    int nbWlen, i;

    amdlibLogTrace("amdlibDisplayWavelength()");


    nbWlen = wavelength->nbWlen;
    printf("nbWlen = %d\n", nbWlen);


    for (i = 0; i < nbWlen; i++)
    {
        printf("nbWlen[%d] = %f - ", i, wavelength->wlen[i]);
        printf("bandWidth[%d] = %f\n", i, wavelength->bandwidth[i]);
    }
}
