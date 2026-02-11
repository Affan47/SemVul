save( QTextStream & ts, int indent )
{
	indentation( &ts, indent );
	ts << "<category race=\"" << _race << "\">" << endl;
	indentation( &ts, indent + 1 );
	ts << "<name>" << getName() << "</name>" << endl;
	indentation( &ts, indent + 1 );
	ts << "<description>" << getName() << "</description>" << endl;
	indentation( &ts, indent + 1 );
	ts << "<evolution>" << endl;
	indentation( &ts, indent + 2 );
	ts << "<characteristic type=\"" << getCharacName( ATTACK ) << "\">";
	ts << _attack << "</characteristic>" << endl;
	indentation( &ts, indent + 2 );
	ts << "<characteristic type=\"" << getCharacName( DEFENSE ) << "\">";
	ts << _defense << "</characteristic>" << endl;
	indentation( &ts, indent + 2 );
	ts << "<characteristic type=\"" << getCharacName( POWER ) << "\">";
	ts << _power << "</characteristic>" << endl;
	indentation( &ts, indent + 2 );
	ts << "<characteristic type=\"" << getCharacName( KNOWLEDGE ) << "\">";
	ts << _knowledge << "</characteristic>" << endl;
	indentation( &ts, indent + 2 );
	ts << "<characteristic type=\"" << getCharacName( CHARISMA ) << "\">";
	ts << _charisma << "</characteristic>" << endl;
	indentation( &ts, indent + 1 );
	ts << "</evolution>" << endl;
	indentation( &ts, indent );
	ts << "</category>" << endl;
}
