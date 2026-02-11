fromPdfRectangle(const PDFRectangle &r) const
{
    double swp, MTX[6];
    fillTransformationMTX(MTX);

    QPointF p1, p2;
    XPDFReader::transform( MTX, r.x1, r.y1, p1 );
    XPDFReader::transform( MTX, r.x2, r.y2, p2 );

    double tl_x = p1.x();
    double tl_y = p1.y();
    double br_x = p2.x();
    double br_y = p2.y();

    if (tl_x > br_x)
    {
        swp = tl_x;
        tl_x = br_x;
        br_x = swp;
    }

    if (tl_y > br_y)
    {
        swp = tl_y;
        tl_y = br_y;
        br_y = swp;
    }

    return QRectF( QPointF(tl_x,tl_y) , QPointF(br_x,br_y) );
}
