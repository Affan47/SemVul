getLordDescription()
{
	ResourceList & themeResources = DataTheme.resources;
	uint nbRes = themeResources.count();
	QString text = "";

	for( uint i = 0; i < nbRes; ++i ) {
		if( getCost( i ) != 0 ) {
			if( text != "" ) {
				text += " + ";
			}
			text += QString::number( getCost( i ) )
				+ " " + themeResources.getRessource( i );
		}
	}
	if( text == "" ) {
		text = "0";
	}
	text =  "Cost: "  + text;
	text +=  "\n" ;
	return text;

}
