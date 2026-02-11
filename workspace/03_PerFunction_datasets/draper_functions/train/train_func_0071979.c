toXml(QDomDocument *doc, bool submitForm) const
{
	QDomElement f = doc->createElement("field");


	if ( !_var.isEmpty() )
		f.setAttribute("var", _var);
	if ( !submitForm && !_label.isEmpty() )
		f.setAttribute("label", _label);


	QString type = "text-single";
	if ( _type == Field_Boolean )
		type = "boolean";
	else if ( _type == Field_Fixed )
		type = "fixed";
	else if ( _type == Field_Hidden )
		type = "hidden";
	else if ( _type == Field_JidMulti )
		type = "jid-multi";
	else if ( _type == Field_JidSingle )
		type = "jid-single";
	else if ( _type == Field_ListMulti )
		type = "list-multi";
	else if ( _type == Field_ListSingle )
		type = "list-single";
	else if ( _type == Field_TextMulti )
		type = "text-multi";
	else if ( _type == Field_TextPrivate )
		type = "text-private";

	f.setAttribute("type", type);


	if ( !submitForm && _required )
		f.appendChild( emptyTag(doc, "required") );

	if ( !submitForm && !_desc.isEmpty() )
		f.appendChild( textTag(doc, "desc", _desc) );

	if ( !submitForm && !_options.isEmpty() ) {
		OptionList::ConstIterator it = _options.begin();
		for ( ; it != _options.end(); ++it) {
			QDomElement o = doc->createElement("option");
			o.appendChild(textTag(doc, "value", (*it).value));
			if ( !(*it).label.isEmpty() )
				o.setAttribute("label", (*it).label);
			f.appendChild(o);
		}
	}

	if ( !_value.isEmpty() ) {
		QStringList::ConstIterator it = _value.begin();
		for ( ; it != _value.end(); ++it)
			f.appendChild( textTag(doc, "value", *it) );
	}

	return f;
}
