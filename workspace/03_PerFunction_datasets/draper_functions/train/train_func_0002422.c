DetectAltText ( XMP_Node * xmpParent )
{
	XMP_Assert ( XMP_ArrayIsAlternate(xmpParent->options) );

	size_t itemNum, itemLim;

	for ( itemNum = 0, itemLim = xmpParent->children.size(); itemNum < itemLim; ++itemNum ) {
		XMP_OptionBits currOptions = xmpParent->children[itemNum]->options;
		if ( (currOptions & kXMP_PropCompositeMask) || (! (currOptions & kXMP_PropHasLang)) ) break;
	}

	if ( (itemLim != 0) && (itemNum == itemLim) ) {
		xmpParent->options |= kXMP_PropArrayIsAltText;
		NormalizeLangArray ( xmpParent );
	}

}
