setColor( const QColor &color )
{
    switch ( d_data->style )
    {
        case QwtSymbol::Ellipse:
        case QwtSymbol::Rect:
        case QwtSymbol::Diamond:
        case QwtSymbol::Triangle:
        case QwtSymbol::UTriangle:
        case QwtSymbol::DTriangle:
        case QwtSymbol::RTriangle:
        case QwtSymbol::LTriangle:
        case QwtSymbol::Star2:
        case QwtSymbol::Hexagon:
        {
            d_data->brush.setColor( color );
            break;
        }
        case QwtSymbol::Cross:
        case QwtSymbol::XCross:
        case QwtSymbol::HLine:
        case QwtSymbol::VLine:
        case QwtSymbol::Star1:
        {
            d_data->pen.setColor( color );
            break;
        }
        default:
        {
            d_data->brush.setColor( color );
            d_data->pen.setColor( color );
        }
    }
}
