PowerSpectrum()
{
    wxCHECK_MSG( Ok(), wxPlotData(), wxT("Invalid wxPlotData, wxPlotData::RunAverage()") );

    wxPlotData power(FFT(true));
    wxCHECK_MSG(power.Ok(), wxPlotData(), wxT("Invalid FFT data curve"));

    int i, count = power.GetCount();
    for (i=0; i<count; i++)
    {
        power.GetYData()[i] = pow(power.GetYData()[i]*power.GetYData()[i] +
                                  power.GetYiData()[i]*power.GetYiData()[i], 0.5)/double(count);
    }

    power.CalcBoundingRect();

    return power;
}
