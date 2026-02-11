load(const QDomElement * e)
{
	if ( e->tagName() != DOM_LANGUAGE_ITEM )
		return;

	QString fileName = QVariant( e->attribute( DOM_LANGUAGE_ITEM_FILE, "" ) ).toString();
	if ( fileName.length() > 0 )
		loadFile( fileName );
	else
		setCode( e->firstChild().toCDATASection().data() );

	float x = QVariant( e->attribute( DOM_LANGUAGE_ITEM_X, "0" ) ).toDouble();
	float y = QVariant( e->attribute( DOM_LANGUAGE_ITEM_Y, "0" )).toDouble();
	setPos(x,y);
	setZValue( QVariant( e->attribute( DOM_LANGUAGE_ITEM_Z, "0" )).toDouble() );
}
