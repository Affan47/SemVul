CloneSubtree ( const XMP_Node * origRoot, XMP_Node * cloneParent )
{
	#if XMP_DebugBuild
		if ( cloneParent->parent == 0 ) {
			XMP_Assert ( origRoot->options & kXMP_SchemaNode );
			XMP_Assert ( FindConstSchema ( cloneParent, origRoot->name.c_str() ) == 0 );
		} else {
			XMP_Assert ( ! (origRoot->options & kXMP_SchemaNode) );
			if ( cloneParent->options & kXMP_PropValueIsStruct ) {
				XMP_Assert ( FindConstChild ( cloneParent, origRoot->name.c_str() ) == 0 );
			}
		}
	#endif

	XMP_Node * cloneRoot = new XMP_Node ( cloneParent, origRoot->name, origRoot->value, origRoot->options );
	CloneOffspring ( origRoot, cloneRoot ) ;
	cloneParent->children.push_back ( cloneRoot );

	return cloneRoot;

}
