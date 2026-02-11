new_image( pagenode *pn, int width, int height )
{
    pn->image = QImage( width, height, QImage::Format_MonoLSB );
    pn->image.setColor( 0, qRgb( 255, 255, 255 ) );
    pn->image.setColor( 1, qRgb( 0, 0, 0 ) );
    pn->bytes_per_line = pn->image.bytesPerLine();
    pn->dpi = FAX_DPI_FINE;
    pn->imageData = new uchar[ width * height ];

    return !pn->image.isNull();
}
