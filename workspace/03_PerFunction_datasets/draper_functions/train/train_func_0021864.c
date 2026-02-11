RepairAltText ( XMP_Node & tree, XMP_StringPtr schemaNS, XMP_StringPtr arrayName )
{
	XMP_Node * schemaNode = FindSchemaNode ( &tree, schemaNS, kXMP_ExistingOnly );
	if ( schemaNode == 0 ) return;

	XMP_Node * arrayNode = FindChildNode ( schemaNode, arrayName, kXMP_ExistingOnly );
	if ( (arrayNode == 0) || XMP_ArrayIsAltText ( arrayNode->options ) ) return;

	if ( ! XMP_PropIsArray ( arrayNode->options ) ) return;


	arrayNode->options |= (kXMP_PropArrayIsOrdered | kXMP_PropArrayIsAlternate | kXMP_PropArrayIsAltText);

	for ( int i = arrayNode->children.size()-1; i >= 0; --i ) {

		XMP_Node * currChild = arrayNode->children[i];

		if ( ! XMP_PropIsSimple ( currChild->options ) ) {


			delete ( currChild );
			arrayNode->children.erase ( arrayNode->children.begin() + i );

		} else if ( ! XMP_PropHasLang ( currChild->options ) ) {

			if ( currChild->value.empty() ) {


				delete ( currChild );
				arrayNode->children.erase ( arrayNode->children.begin() + i );

			} else {


				XMP_Node * repairLang = new XMP_Node ( currChild, "xml:lang", "x-repair", kXMP_PropIsQualifier );
				if ( currChild->qualifiers.empty() ) {
					currChild->qualifiers.push_back ( repairLang );
				} else {
					currChild->qualifiers.insert ( currChild->qualifiers.begin(), repairLang );
				}
				currChild->options |= (kXMP_PropHasQualifiers | kXMP_PropHasLang);

			}

		}

	}

}
