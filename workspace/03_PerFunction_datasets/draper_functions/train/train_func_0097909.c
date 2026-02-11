createAnnotation( const QDomElement & annElement )
{

    if ( !annElement.hasAttribute( "type" ) )
        return 0;


    Annotation * annotation = 0;
    int typeNumber = annElement.attribute( "type" ).toInt();
    switch ( typeNumber )
    {
        case Annotation::AText:
            annotation = new TextAnnotation( annElement );
            break;
        case Annotation::ALine:
            annotation = new LineAnnotation( annElement );
            break;
        case Annotation::AGeom:
            annotation = new GeomAnnotation( annElement );
            break;
        case Annotation::AHighlight:
            annotation = new HighlightAnnotation( annElement );
            break;
        case Annotation::AStamp:
            annotation = new StampAnnotation( annElement );
            break;
        case Annotation::AInk:
            annotation = new InkAnnotation( annElement );
            break;
        case Annotation::ACaret:
            annotation = new CaretAnnotation( annElement );
            break;
    }


    return annotation;
}
