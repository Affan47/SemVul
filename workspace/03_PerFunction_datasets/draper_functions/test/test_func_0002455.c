saveToDomElement( QDomDocument * doc)
{
	QDomElement element = doc->createElement( DOM_LANGUAGE_ITEM );

	element.setAttribute( DOM_LANGUAGE_ITEM_X, pos().x() );
	element.setAttribute( DOM_LANGUAGE_ITEM_Y, pos().y() );
	element.setAttribute( DOM_LANGUAGE_ITEM_Z, zValue() );

	if ( file().length() > 0 )
		element.setAttribute( DOM_LANGUAGE_ITEM_FILE , file() );
	else
	{
		QDomCDATASection codeSection = doc->createCDATASection( code() );
		element.appendChild(codeSection);
	}

	return element;
}
