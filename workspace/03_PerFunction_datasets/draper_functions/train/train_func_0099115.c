fromXml(const QDomElement &e)
{
	if ( (e.attribute("xmlns") != "jabber:x:data") && (e.namespaceURI() != "jabber:x:data") )
		return;

	QString type = e.attribute("type");
	if ( type == "result" )
		d->type = Data_Result;
	else if ( type == "submit" )
		d->type = Data_Submit;
	else if ( type == "cancel" )
		d->type = Data_Cancel;
	else
		d->type = Data_Form;

	d->title        = subTagText(e, "title");
	d->instructions = subTagText(e, "instructions");

	d->fields.clear();

	QDomNode n = e.firstChild();
	for ( ; !n.isNull(); n = n.nextSibling() ) {
		QDomElement i = n.toElement();
		if ( i.isNull() )
			continue;

		if ( i.tagName() == "field" ) {
			Field f;
			f.fromXml(i);
			d->fields.append(f);
		}
		else if ( i.tagName() == "reported" ) {
			d->report.clear();
			d->reportItems.clear();

			QDomNode nn = i.firstChild();
			for ( ; !nn.isNull(); nn = nn.nextSibling() ) {
				QDomElement ii = nn.toElement();
				if ( ii.isNull() )
					continue;

				if ( ii.tagName() == "field" ) {
					d->report.append( ReportField( ii.attribute("label"), ii.attribute("var") ) );
				}
			}
		}
		else if ( i.tagName() == "item" ) {
			ReportItem item;

			QDomNode nn = i.firstChild();
			for ( ; !nn.isNull(); nn = nn.nextSibling() ) {
				QDomElement ii = nn.toElement();
				if ( ii.isNull() )
					continue;

				if ( ii.tagName() == "field" ) {
					QString name = ii.attribute("var");
					QString value;

					bool found;
					QDomElement e = findSubTag( ii, "value", &found );
					if ( found )
						value = e.text();

					item[name] = value;
				}
			}

			d->reportItems.append( item );
		}
	}
}
