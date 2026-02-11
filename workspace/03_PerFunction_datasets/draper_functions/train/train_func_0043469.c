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

	switch( field->type )
	{
	case CSFC_FILENAME:
		Filename = ParseFieldString(field);
		return begin;

	case CSFC_FOLDER_FLAG:
		FolderFlag = false;
		{


			string s = ParseFieldString(field);
			if( s == "folder" ) {
				FolderFlag = true;
			}
		}
		return begin;

	case CSFC_FILE_CONTENT:
		if( FileSize ) {

			FileContent.append((const char*)field->u.raw,
				btohs(field->size));
		}
		else {
			FileSize = btohll(field->u.uint64);
		}
		return begin;

	case CSFC_FILE_DESCRIPTOR:


		FileDescriptor.assign((const char*)field->u.raw,
			btohs(field->size));
		return begin;
	}


	UnknownField uf;
	uf.type = field->type;
	uf.data.assign((const char*)field->u.raw, btohs(field->size));
	Unknowns.push_back(uf);


	return begin;
}
