ItemValuesMatch ( const XMP_Node * leftNode, const XMP_Node * rightNode )
{
	const XMP_OptionBits leftForm  = leftNode->options & kXMP_PropCompositeMask;
	const XMP_OptionBits rightForm = leftNode->options & kXMP_PropCompositeMask;

	if ( leftForm != rightForm ) return false;

	if ( leftForm == 0 ) {


		if ( leftNode->value != rightNode->value ) return false;
		if ( (leftNode->options & kXMP_PropHasLang) != (rightNode->options & kXMP_PropHasLang) ) return false;
		if ( leftNode->options & kXMP_PropHasLang ) {
			if ( leftNode->qualifiers[0]->value != rightNode->qualifiers[0]->value ) return false;
		}

	} else if ( leftForm == kXMP_PropValueIsStruct ) {


		if ( leftNode->children.size() != rightNode->children.size() ) return false;

		for ( size_t leftNum = 0, leftLim = leftNode->children.size(); leftNum != leftLim; ++leftNum ) {
			const XMP_Node * leftField	= leftNode->children[leftNum];
			const XMP_Node * rightField = FindConstChild ( rightNode, leftField->name.c_str() );
			if ( (rightField == 0) || (! ItemValuesMatch ( leftField, rightField )) ) return false;
		}

	} else {


		XMP_Assert ( leftForm & kXMP_PropValueIsArray );

		for ( size_t leftNum = 0, leftLim = leftNode->children.size(); leftNum != leftLim; ++leftNum ) {

			const XMP_Node * leftItem = leftNode->children[leftNum];

			size_t rightNum, rightLim;
			for ( rightNum = 0, rightLim = rightNode->children.size(); rightNum != rightLim; ++rightNum ) {
				const XMP_Node * rightItem = rightNode->children[rightNum];
				if ( ItemValuesMatch ( leftItem, rightItem ) ) break;
			}
			if ( rightNum == rightLim ) return false;

		}

	}

	return true;

}
