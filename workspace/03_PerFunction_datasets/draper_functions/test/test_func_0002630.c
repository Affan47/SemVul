updateTabOrder()
{
    if ( d_data->canvas->focusPolicy() == Qt::NoFocus )
        return;
    if ( d_data->legend.isNull()
        || d_data->layout->legendPosition() == ExternalLegend
        || d_data->legend->legendItems().count() == 0 )
    {
        return;
    }


    const bool canvasFirst =
        d_data->layout->legendPosition() == QwtPlot::BottomLegend ||
        d_data->layout->legendPosition() == QwtPlot::RightLegend;

    QWidget *previous = NULL;

    QWidget *w = d_data->canvas;
    while ( ( w = w->nextInFocusChain() ) != d_data->canvas )
    {
        bool isLegendItem = false;
        if ( w->focusPolicy() != Qt::NoFocus
            && w->parent() && w->parent() == d_data->legend->contentsWidget() )
        {
            isLegendItem = true;
        }

        if ( canvasFirst )
        {
            if ( isLegendItem )
                break;

            previous = w;
        }
        else
        {
            if ( isLegendItem )
                previous = w;
            else
            {
                if ( previous )
                    break;
            }
        }
    }

    if ( previous && previous != d_data->canvas )
        setTabOrder( previous, d_data->canvas );
}
