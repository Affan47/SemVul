CollectNamespaceDecls ( NamespaceMap * nsMap, const XML_Node & node )
{
	size_t i, limit;

	if ( ! node.ns.empty() ) {
		size_t nameMid = 0;
		while ( node.name[nameMid] != ':' ) ++nameMid;
		std::string prefix = node.name.substr ( 0, nameMid );
		(*nsMap)[prefix] = node.ns;
	}

	if ( node.kind == kElemNode ) {

		for ( i = 0, limit = node.attrs.size(); i < limit; ++i ) {
			CollectNamespaceDecls ( nsMap, *node.attrs[i] );
		}

		for ( i = 0, limit = node.content.size(); i < limit; ++i ) {
			const XML_Node & content = *node.content[i];
			if ( content.kind == kElemNode ) CollectNamespaceDecls ( nsMap, content );
		}

	}

}
