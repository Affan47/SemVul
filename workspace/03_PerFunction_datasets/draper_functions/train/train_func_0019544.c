get_attribute(parse_context_t* context, int nb_attributes,	const xmlChar** attributes, const xmlChar* name) {

	xmlChar *value=NULL;

	int index;
	for(index=0; index<nb_attributes && value==NULL; index++) {
		int att_index = index * 5;

		const xmlChar *localname = attributes[att_index];
		if(xmlStrEqual(name, localname)) {


			const xmlChar *valueBegin = attributes[att_index+3];
			const xmlChar *valueEnd = attributes[att_index+4];

			int value_size = valueEnd - valueBegin;
			value = xmlStrsub(valueBegin, 0, value_size);
		}

	}

	return value;
}
