tabHeight( const QString& txt, QWidget* widget ) const
{
    QStyleOptionHeader opt;
    if ( widget ) opt.initFrom( widget );
    opt.text = txt;
    QStyle* style;
    if ( widget ) style = widget->style();
    else style = QApplication::style();
    QSize s = style->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), widget);
    return s.height();
}
