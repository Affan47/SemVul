Derivitive() const
{
    wxCHECK_MSG( Ok(), wxPlotData(), wxT("Invalid wxPlotData") );

    int count = M_PLOTDATA->m_count;

    wxPlotData dst(count, false);

    double *y_data = M_PLOTDATA->m_Ydata;
    double *dst_y_data = dst.GetYData();

    memcpy(dst.GetXData(), GetXData(), count*sizeof(double));

    *dst_y_data++ = 0;

    for (int i=1; i<count-1; i++)
    {
        y_data++;

        if (wxFinite(*(y_data)) && wxFinite(*(y_data-1)))
            *dst_y_data++ = (*(y_data)) - (*(y_data-1));
        else
            *dst_y_data++ = 0;
    }

    *dst_y_data = 0;

    dst.CalcBoundingRect();
    return dst;
}
