startElement( const QString &, const QString &, const QString & qName, const QXmlAttributes & atts )
{
	if( qName == "lordCategories" && _state == StateInit ) {
		_state = StateDocument;
	} else if ( qName == "category" && _state == StateDocument ) {
		_state = StateCategory;
		_category = new LordCategoryModel();
		_category->setRace( atts.value( "race" ).toUInt() );
	} else if ( qName == "name" && _state == StateCategory ) {
		_state = StateName;
	} else if( qName == "description" && _state == StateCategory ) {
		_state = StateDescription;
	} else if( qName == "evolution" && _state == StateCategory ) {
		_state = StateEvolution;
	} else if( qName == "characteristic" && _state == StateEvolution ) {
		_state = StateCharac;
		charac = detectCharac( atts.value( "type" ) );
	} else {

		return false;
	}
	return true;
}
