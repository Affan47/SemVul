SetLegacyMetaData ( XML_Node *		clipMetadata,
						 SXMPMeta *		xmpObj,
						 XMP_StringPtr	legacyNS )
{
	bool updateLegacyXML = false;
	bool xmpFound = false;
	std::string xmpValue;
	XML_Node * xmlNode = 0;

	xmpFound = xmpObj->GetProperty ( kXMP_NS_DC, "title", &xmpValue, 0 );

	if ( xmpFound ) {

		xmlNode = CreateChildElement ( clipMetadata, "Title", legacyNS, 3 );
		if ( xmpValue != xmlNode->GetLeafContentValue() ) {
			xmlNode->SetLeafContentValue ( xmpValue.c_str() );
			updateLegacyXML = true;
		}

	}

	xmpFound = xmpObj->GetArrayItem ( kXMP_NS_DC, "creator", 1, &xmpValue, 0 );

	if ( xmpFound ) {
		xmlNode = CreateChildElement ( clipMetadata, "Creator", legacyNS, 3 );
		XMP_StringPtr creatorName = xmlNode->GetAttrValue ( "name" );
		if ( creatorName == 0 ) creatorName = "";
		if ( xmpValue != creatorName ) {
			xmlNode->SetAttrValue ( "name", xmpValue.c_str() );
			updateLegacyXML = true;
		}
	}

	xmpFound = xmpObj->GetProperty ( kXMP_NS_DC, "description", &xmpValue, 0 );

	if ( xmpFound ) {
		xmlNode = CreateChildElement ( clipMetadata, "Description", legacyNS, 3 );
		if ( xmpValue != xmlNode->GetLeafContentValue() ) {

			if ( xmpValue.size() > 2047 ) xmpValue.resize ( 2047 );
			xmlNode->SetLeafContentValue ( xmpValue.c_str() );
			updateLegacyXML = true;
		}
	}

	return updateLegacyXML;

}
