Copy( const wxPlotData &source, bool copy_all )
{
    wxCHECK_MSG( source.Ok(), false, wxT("Invalid wxPlotData") );

    int count = source.GetCount();

    if (!Create(count, false)) return false;

    memcpy( M_PLOTDATA->m_Xdata, source.GetXData(), count*sizeof(double) );
    memcpy( M_PLOTDATA->m_Ydata, source.GetYData(), count*sizeof(double) );

    if (source.GetYiData())
    {
        M_PLOTDATA->m_Yidata = (double*)malloc(count*sizeof(double));
        if (!M_PLOTDATA->m_Yidata)
        {
            UnRef();
            return false;
        }
        memcpy( M_PLOTDATA->m_Yidata, source.GetYiData(), count*sizeof(double) );
    }

    if (copy_all)
        CopyExtra(source);

    CalcBoundingRect();
    return true;
}
