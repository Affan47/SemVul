fromQuadrilaterals(AnnotQuadrilaterals *hlquads) const
{
    QList< HighlightAnnotation::Quad > quads;

    if ( !hlquads || !hlquads->getQuadrilateralsLength() )
        return quads;
    const int quadsCount = hlquads->getQuadrilateralsLength();

    double MTX[6];
    fillTransformationMTX(MTX);

    for (int q = 0; q < quadsCount; ++q)
    {
        HighlightAnnotation::Quad quad;
        XPDFReader::transform( MTX, hlquads->getX1( q ), hlquads->getY1( q ), quad.points[ 0 ] );
        XPDFReader::transform( MTX, hlquads->getX2( q ), hlquads->getY2( q ), quad.points[ 1 ] );
        XPDFReader::transform( MTX, hlquads->getX3( q ), hlquads->getY3( q ), quad.points[ 2 ] );
        XPDFReader::transform( MTX, hlquads->getX4( q ), hlquads->getY4( q ), quad.points[ 3 ] );


        QPointF tmpPoint = quad.points[ 2 ];
        quad.points[ 2 ] = quad.points[ 3 ];
        quad.points[ 3 ] = tmpPoint;

        quad.capStart = true;
        quad.capEnd = true;
        quad.feather = 0.1;
        quads.append( quad );
    }

    return quads;
}
