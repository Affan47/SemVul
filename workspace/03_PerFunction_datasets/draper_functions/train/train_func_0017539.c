writeReferencePtr( InputLoc &loc, Definition *prod, char *data, int refNum )
{
	bool user = false, refThis = false;
	int rhsPos = -1;

	if ( data[0] == '$' )
		user = true;

	if ( data[1] == '$' || data[1] == '@' )
		refThis = true;
	else
		rhsPos = atoi(data+1);


	KlangEl *lel = refThis ? prod->prodName : prod->rhsLelVect[rhsPos-1];

	if ( user ) {
		if ( lel == 0 || lel->type == KlangEl::Term ) {
			if ( tokenIsClass )
				out << Token() << " *__ref" << refNum << " = (" << Token() << "*)";
			else
				out << Token() << " *__ref" << refNum << " = (" << Token() << "*)&";
		}
		else if ( lel != 0 && lel->type == KlangEl::NonTerm  ) {
			if ( lel->typeDef != 0 && lel->typeDef->isClass )
				out << Lel_() << lel->typeDef->data << " *__ref" << refNum << " = (" << Lel_() << lel->typeDef->data << "*)";
			else
				out << Lel_() << lel->typeDef->data << " *__ref" << refNum << " = (" << Lel_() << lel->typeDef->data << "*)&";
		}
		else {
			assert( false );
		}
	}
	else {
		out << LangEl() << " *__ref" << refNum << " = (" << LangEl() << "*)";
	}


	if ( refThis )
		out << "redLel";
	else
		out << "rhs[" << (rhsPos-1) << "]";

	if ( user ) {
		if ( lel == 0 || lel->type == KlangEl::Term ) {

			out << "->user.token";
		}
		else if ( lel->type == KlangEl::NonTerm && lel->typeDef != 0 )
			out << "->user." << lel->typeDef->data;
		else {
			error(loc) << "reference to " << data << " in code block "
					"does not have a user type" << endl;
			exit(1);
		}
	}

	out << ";\n";
}
