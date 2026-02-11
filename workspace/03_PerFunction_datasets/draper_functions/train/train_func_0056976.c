CompareSubtrees ( const XMP_Node & leftNode, const XMP_Node & rightNode )
{

	if ( (leftNode.value != rightNode.value) ||
	     (leftNode.options != rightNode.options) ||
	     (leftNode.children.size() != rightNode.children.size()) ||
	     (leftNode.qualifiers.size() != rightNode.qualifiers.size()) ) return false;


	for ( size_t qualNum = 0, qualLim = leftNode.qualifiers.size(); qualNum != qualLim; ++qualNum ) {
		const XMP_Node * leftQual  = leftNode.qualifiers[qualNum];
		const XMP_Node * rightQual = FindConstQualifier ( &rightNode, leftQual->name.c_str() );
		if ( (rightQual == 0) || (! CompareSubtrees ( *leftQual, *rightQual )) ) return false;
	}

	if ( (leftNode.parent == 0) || (leftNode.options & (kXMP_SchemaNode | kXMP_PropValueIsStruct)) ) {


		for ( size_t childNum = 0, childLim = leftNode.children.size(); childNum != childLim; ++childNum ) {
			const XMP_Node * leftChild  = leftNode.children[childNum];
			const XMP_Node * rightChild = FindConstChild ( &rightNode, leftChild->name.c_str() );
			if ( (rightChild == 0) || (! CompareSubtrees ( *leftChild, *rightChild )) ) return false;
		}

	} else if ( leftNode.options & kXMP_PropArrayIsAltText ) {


		for ( size_t childNum = 0, childLim = leftNode.children.size(); childNum != childLim; ++childNum ) {
			const XMP_Node * leftChild = leftNode.children[childNum];
			XMP_Assert ( (! leftChild->qualifiers.empty()) && (leftChild->qualifiers[0]->name == "xml:lang") );
			XMP_Index rightIndex = LookupLangItem ( &rightNode, leftChild->qualifiers[0]->value );
			if ( rightIndex == -1 ) return false;
			const XMP_Node * rightChild = rightNode.children[rightIndex];
			if ( ! CompareSubtrees ( *leftChild, *rightChild ) ) return false;
		}

	} else {


		XMP_Assert ( (! (leftNode.options & kXMP_PropCompositeMask)) || (leftNode.options & kXMP_PropValueIsArray) );
		for ( size_t childNum = 0, childLim = leftNode.children.size(); childNum != childLim; ++childNum ) {
			const XMP_Node * leftChild  = leftNode.children[childNum];
			const XMP_Node * rightChild = rightNode.children[childNum];
			if ( ! CompareSubtrees ( *leftChild, *rightChild ) ) return false;
		}

	}

	return true;

}
