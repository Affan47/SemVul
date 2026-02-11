ogr2extrude_rec (
    int nExtrude,
    GeometryPtr poKmlGeometry )
{

    PointPtr poKmlPoint;
    LineStringPtr poKmlLineString;
    PolygonPtr poKmlPolygon;
    MultiGeometryPtr poKmlMultiGeometry;

    size_t nGeom;
    size_t i;

    switch ( poKmlGeometry->Type (  ) ) {
    case kmldom::Type_Point:
        poKmlPoint = AsPoint ( poKmlGeometry );
        poKmlPoint->set_extrude ( nExtrude );
        break;

    case kmldom::Type_LineString:
        poKmlLineString = AsLineString ( poKmlGeometry );
        poKmlLineString->set_extrude ( nExtrude );
        break;

    case kmldom::Type_LinearRing:
        break;

    case kmldom::Type_Polygon:
        poKmlPolygon = AsPolygon ( poKmlGeometry );
        poKmlPolygon->set_extrude ( nExtrude );
        break;

    case kmldom::Type_MultiGeometry:
        poKmlMultiGeometry = AsMultiGeometry ( poKmlGeometry );

        nGeom = poKmlMultiGeometry->get_geometry_array_size (  );
        for ( i = 0; i < nGeom; i++ ) {
            ogr2extrude_rec ( nExtrude,
                              poKmlMultiGeometry->
                              get_geometry_array_at ( i ) );
        }
        break;

    default:
        break;

    }
}
