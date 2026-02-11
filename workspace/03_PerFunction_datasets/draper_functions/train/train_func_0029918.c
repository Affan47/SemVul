FFT( bool forward )
{
    wxCHECK_MSG( Ok(), wxPlotData(), wxT("Invalid wxPlotData") );
    wxCHECK_MSG( GetCount() < 2, wxPlotData(), wxT("Invalid wxPlotData size") );


    int samples    = 1;
    int orig_count = M_PLOTDATA->m_count;
    while (samples < orig_count) samples *= 2;

    wxPlotData source;
    source.Copy(*this);


    if (samples > orig_count)
    {
        double dx = M_PLOTDATA->m_Xdata[1] - M_PLOTDATA->m_Xdata[0];
        source.Resize(samples, dx, M_PLOTDATA->m_Ydata[orig_count - 1]);
    }

    wxPlotData trans(samples);
    trans.SetYiData( (double*)malloc(samples*sizeof(double)) );

    if (fft_double( samples, (forward ? 0 : 1),
                    source.GetYData(), source.GetYiData(),
                    trans.GetYData(),  trans.GetYiData() ) == 0)
        return wxPlotData();

    if (forward)
    {
        double *trans_xData = trans.GetXData();
        trans_xData[0] = 0.0;
        double timestep = (M_PLOTDATA->m_Xdata[1] - M_PLOTDATA->m_Xdata[0])*samples;
        for (int i=0; i<samples; i++)
        {
            trans_xData[i] = double(i)/timestep;
        }


    }
    else
    {
        double *trans_xData  = trans.GetXData();
        double timestep = 1.0/((M_PLOTDATA->m_Xdata[1] - M_PLOTDATA->m_Xdata[0])*double(samples));
        for (int i=0; i<samples; i++)
        {
            trans_xData[i] = timestep*double(i);
        }
    }

    trans.CalcBoundingRect();
    return trans;
}
