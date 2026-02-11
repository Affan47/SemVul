heightForWidth( int width ) const
{
    const int renderFlags = d_data->text.renderFlags();

    int indent = d_data->indent;
    if ( indent <= 0 )
        indent = defaultIndent();

    width -= 2 * frameWidth();
    if ( renderFlags & Qt::AlignLeft || renderFlags & Qt::AlignRight )
        width -= indent;

    int height = d_data->text.heightForWidth( width, font() );
    if ( renderFlags & Qt::AlignTop || renderFlags & Qt::AlignBottom )
        height += indent;

    height += 2 * frameWidth();

    return height;
}
