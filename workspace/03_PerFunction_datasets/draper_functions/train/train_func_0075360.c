GetYiData() const
{
    wxCHECK_MSG( Ok(), (double*)NULL, wxT("Invalid wxPlotData") );
    return M_PLOTDATA->m_Yidata;
}
