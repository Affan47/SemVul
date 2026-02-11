getStyleOption( const QModelIndex& index ) const
{
    StyleOptionGanttItem opt;
    opt.displayPosition = StyleOptionGanttItem::Right;
    opt.displayAlignment = Qt::Alignment( d->proxyModel.data( index, Qt::TextAlignmentRole ).toInt() );
    opt.text = index.model()->data( index, LegendRole ).toString();
    opt.font = qVariantValue< QFont >( index.model()->data( index, Qt::FontRole ) );
    return opt;
}
