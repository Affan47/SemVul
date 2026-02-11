select(const QPoint &pos, bool clicked)
{
    QwtPlotCurve *curve = NULL;
    double dist = 10e10;
    int index = -1;

    const QwtPlotItemList& itmList = plot()->itemList();
    for ( QwtPlotItemIterator it = itmList.begin();
        it != itmList.end(); ++it )
    {
        if ( (*it)->rtti() == QwtPlotItem::Rtti_PlotCurve )
        {
            QwtPlotCurve *c = (QwtPlotCurve*)(*it);

            double d = -1;
            int idx = c->closestPoint(pos, &d);
            if ( d != -1 && d < dist )
            {
                curve = c;
                index = idx;
                dist = d;
            }
        }
    }

    d_selectedCurve = NULL;
    d_selectedPoint = -1;

    if ( curve && dist < 10 )
    {

        d_selectedCurve = curve;
        d_selectedPoint = index;

        if (clicked)
            pointClicked(curve, index);
        else
            pointHover(curve, index);
    } else {

        if (clicked)
            pointClicked(NULL, -1);
        else
            pointHover(NULL, -1);

    }
}
