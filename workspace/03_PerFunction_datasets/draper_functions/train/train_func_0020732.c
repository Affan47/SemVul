ParseField(const unsigned char *begin,
					 const unsigned char *end,
					 const IConverter *ic)
{
	const CommonField *field = (const CommonField *) begin;


	begin += COMMON_FIELD_HEADER_SIZE + btohs(field->size);
	if( begin > end )
		return begin;

	if( !btohs(field->size) )
		return begin;


	for(	FieldLink<MessageBase> *b = MessageBaseFieldLinks;
		b->type != MBFC_END;
		b++ )
	{
		if( b->type == field->type ) {
			if( b->strMember ) {

				std::string &s = this->*(b->strMember);
				s = ParseFieldString(field);
				if( b->iconvNeeded && ic )
					s = ic->FromBB(s);
				return begin;
			}
			else if( b->addrMember ) {


				const char *fa = (const char*)field->u.addr.addr;
				std::string dual(fa, btohs(field->size) - sizeof(field->u.addr.unknown));


				EmailAddress a;
				a.Name = dual.c_str();


				a.Email = dual.c_str() + a.Name.size() + 1;


				if( a.size() ) {

					if( b->iconvNeeded && ic ) {
						a.Name = ic->FromBB(a.Name);
						a.Email = ic->FromBB(a.Email);
					}

					EmailAddressList &al = this->*(b->addrMember);
					al.push_back(a);
				}

				return begin;
			}
		}
	}


	switch( field->type )
	{
	case MBFC_RECORDID:
		MessageRecordId = btohl(field->u.uint32);
		return begin;

	case MBFC_REPLY_UNKNOWN:

		return begin;
	}


	UnknownField uf;
	uf.type = field->type;
	uf.data.assign((const char*)field->u.raw, btohs(field->size));
	Unknowns.push_back(uf);

	return begin;
}
