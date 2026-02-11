SetBox ( BoxRef theBox, const void* dataPtr, XMP_Uns32 size )
{
	XMP_Enforce ( size < moovBoxSizeLimit );
	BoxNode * node = (BoxNode*)theBox;

	if ( node->contentSize == size ) {

		XMP_Uns8 * oldContent = PickContentPtr ( *node );
		if ( memcmp ( oldContent, dataPtr, size ) == 0 ) return;
		memcpy ( oldContent, dataPtr, size );
		this->moovNode.changed = true;

		#if TraceUpdateMoovTree
			XMP_Uns32 be32 = MakeUns32BE ( node->boxType );
			fprintf ( stderr, "Updated '%.4s', parse offset 0x%X, same size\n", &be32, node->offset );
		#endif

	} else {

		node->changedContent.assign ( size, 0 );
		memcpy ( &node->changedContent[0], dataPtr, size );
		node->contentSize = size;
		node->changed = true;
		this->moovNode.changed = true;

		#if TraceUpdateMoovTree
			XMP_Uns32 be32 = MakeUns32BE ( node->boxType );
			XMP_Uns32 addr32 = (XMP_Uns32) this->PickContentPtr ( *node );
			fprintf ( stderr, "Updated '%.4s', parse offset 0x%X, new size %d, new content @ 0x%X\n",
					  &be32, node->offset, node->contentSize, addr32 );
		#endif

	}

}
