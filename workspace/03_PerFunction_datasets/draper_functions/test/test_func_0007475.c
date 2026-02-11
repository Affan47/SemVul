Dump(std::ostream &os) const
{
	ios_format_state state(os);

	os.setf(ios::left);
	os.fill(' ');

	os << _("Contact: ") << "0x" << setbase(16) << GetID()
		<< " (" << (unsigned int)RecType << ")\n";


	os << "    " << setw(20) << _("FirstName");
	os << ": " << FirstName << "\n";
	os << "    " << setw(20) << _("LastName");
	os << ": " << LastName << "\n";


	EmailList::const_iterator eai = EmailAddresses.begin();
	for( ; eai != EmailAddresses.end(); ++eai ) {
		if( eai->size() ) {
			os << _("    Email               : ") << *eai << "\n";
		}
	}


	for(	FieldLink<Contact> *b = ContactFieldLinks;
		b->type != CFC_INVALID_FIELD;
		b++ )
	{


		if( b->type == CFC_IMAGE )
			continue;

		const std::string *pField = 0;
		if( b->strMember ) {
			pField = &(this->*(b->strMember));
		}
		else if( b->postMember && b->postField ) {
			pField = &((this->*(b->postMember)).*(b->postField));
		}


		if( pField && pField->size() ) {
			os << "    " << setw(20) << gettext(b->name);
			os << ": " << Cr2LfWrapper(*pField) << "\n";
		}
	}

	if( Categories.size() ) {
		string display;
		Categories.CategoryList2Str(display);
		os << _("    Categories          : ") << display << "\n";
	}


	if( Birthday.HasData() ) {
		os << _("    Birthday            : ") << Birthday << "\n";
	}
	if( Anniversary.HasData() ) {
		os << _("    Anniversary         : ") << Anniversary << "\n";
	}


	GroupLinksType::const_iterator
		gb = GroupLinks.begin(), ge = GroupLinks.end();
	if( gb != ge )
		os << _("    GroupLinks:\n");
	for( ; gb != ge; gb++ ) {
		os << _("        ID: ") << "0x" << setbase(16) << gb->Link << "\n";
	}


	if( Image.size() ) {
		Data image(Image.data(), Image.size());
		os << _("    Photo image:\n");
		os << image << "\n";
	}


	os << Unknowns;
}
