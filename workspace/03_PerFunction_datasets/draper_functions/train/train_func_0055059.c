Variance(int start_index, int count) const
{
    wxCHECK_MSG( Ok(), 0, wxT("Invalid wxPlotData") );
    int points = M_PLOTDATA->m_count;
    if (count <= 0) count = points - start_index;
    wxCHECK_MSG((start_index >= 0) && (start_index + count <= points), 0, wxT("invalid index"));

    double *y_data = GetYData() + start_index;
    double sum = 0;
    double ave = GetAverage(start_index, count);

    for (register int i=0; i<count; i++)
    {
        sum += ((*y_data) - ave)*((*y_data) - ave);
        y_data++;
    }

    return sqrt(sum/count);
}
