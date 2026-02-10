dirac_encoder_load (dirac_encoder_t *encoder, unsigned char *uncdata, int uncdata_size)
{
    TEST (encoder != NULL);
    TEST (encoder->compressor != NULL);
    DiracEncoder *compressor = (DiracEncoder *)encoder->compressor;
    int ret_stat = 0;
    try
    {
        if ( compressor->LoadNextFrame (uncdata, uncdata_size))
        {
            ret_stat = uncdata_size;
        }
    }
    catch (...)
    {
        if (compressor->GetEncParams().Verbose())
            std::cerr << "dirac_encoder_load failed" << std::endl;
        ret_stat = -1;
    }
    return ret_stat;
}
