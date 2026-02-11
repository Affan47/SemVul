legendItem() const
{
    QwtLegendItem *item = new QwtLegendItem;
    if ( d_data->plot )
    {
        QObject::connect( item, SIGNAL( clicked() ),
            d_data->plot, SLOT( legendItemClicked() ) );
        QObject::connect( item, SIGNAL( checked( bool ) ),
            d_data->plot, SLOT( legendItemChecked( bool ) ) );
    }
    return item;
}
