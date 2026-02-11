freeInput ()
{
    if (getDimInputProb () > 0)
    {
        delete [] d_inputProb_p; d_inputProb_p = 0;
    }

    d_dimInputProb = 0;
}
