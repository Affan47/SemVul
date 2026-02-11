Deviation( const wxPlotData &data, int min, int max ) const
{
    wxCHECK_MSG( Ok() && data.Ok(), 0.0, wxT("Invalid wxPlotData") );
    const int count = GetCount();
    wxCHECK_MSG((min >= 0)&&(min<count), 0.0, wxT("invalid min index"));
    if (max < 0) max = count;
    wxCHECK_MSG(max > min, 0.0, wxT("invalid index range"));

    double data_x_min = data.GetBoundingRect().GetLeft();
    double data_x_max = data.GetBoundingRect().GetRight();
    const int data_count = data.GetCount();

    double *x_data = M_PLOTDATA->m_Xdata + min;
    double *y_data = M_PLOTDATA->m_Ydata + min;

    double x, y, dev = 0.0;

    int index1=0, index2=0;
    int points = 0;
    register int i;

    for (i=min; i<max; i++)
    {
        x = GetXValue(i);
        y = GetYValue(i);

        if ( (x >= data_x_min) && (x <= data_x_max) )
        {
            index1 = data.GetIndexFromX(x);
            if ( data.GetXValue(index1) == x )
            {
                double yd = (y - data.GetYValue(index1));
                dev += yd*yd;
                points++;
            }
            else
            {
                if (x < data.GetXValue(index1))
                {
                    index2 = index1;
                    index1--;
                }
                else
                {
                    index2 = index1 + 1;
                }

                if ((index1 >= 0) && (index2 < data_count) )
                {
                    double yd = y - LinearInterpolateY( data.GetXValue(index1), data.GetYValue(index1),
                                                        data.GetXValue(index2), data.GetYValue(index2), x );
                    dev += yd*yd;
                    points++;
                }
            }
        }
        x_data++;
        y_data++;
    }

    dev = sqrt(dev);

    if (points > 0)
        return dev/double(points);

    return -1;
}
