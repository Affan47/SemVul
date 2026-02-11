PowerY( double power, int start_index, int end_index )
{
    wxCHECK_RET( Ok(), wxT("Invalid wxPlotData") );
    const int count = M_PLOTDATA->m_count;
    if (end_index < 0) end_index = count - 1;
    CHECK_START_END_INDEX_RET(start_index, end_index, count);

    register int i;
    double *y = M_PLOTDATA->m_Ydata + start_index;
    for (i = start_index; i <= end_index; i++, y++)
        *y = pow(*y, power);

    CalcBoundingRect();
}
