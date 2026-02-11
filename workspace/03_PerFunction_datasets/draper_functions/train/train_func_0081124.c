SerializeCompactRDFSchemas ( const XMP_Node & xmpTree,
							 XMP_VarString &  outputStr,
							 XMP_StringPtr	  newline,
							 XMP_StringPtr	  indentStr,
							 XMP_Index		  baseIndent )
{
	XMP_Index level;
	size_t schema, schemaLim;


	for ( level = baseIndent+2; level > 0; --level ) outputStr += indentStr;
	outputStr += kRDF_SchemaStart;
	outputStr += '"';
	outputStr += xmpTree.name;
	outputStr += '"';


	size_t totalLen = 8;
	XMP_cStringMapPos currPos = sNamespacePrefixToURIMap->begin();
	XMP_cStringMapPos endPos  = sNamespacePrefixToURIMap->end();
	for ( ; currPos != endPos; ++currPos ) totalLen += currPos->first.size();

	XMP_VarString usedNS;
	usedNS.reserve ( totalLen );
	usedNS = "xml:rdf:";

	for ( schema = 0, schemaLim = xmpTree.children.size(); schema != schemaLim; ++schema ) {
		const XMP_Node * currSchema = xmpTree.children[schema];
		DeclareUsedNamespaces ( currSchema, usedNS, outputStr, newline, indentStr, baseIndent+4 );
	}


	bool allAreAttrs = true;
	for ( schema = 0, schemaLim = xmpTree.children.size(); schema != schemaLim; ++schema ) {
		const XMP_Node * currSchema = xmpTree.children[schema];
		allAreAttrs &= SerializeCompactRDFAttrProps ( currSchema, outputStr, newline, indentStr, baseIndent+3 );
	}
	if ( ! allAreAttrs ) {
		outputStr += ">";
		outputStr += newline;
	} else {
		outputStr += "/>";
		outputStr += newline;
		return;
	}


	for ( schema = 0, schemaLim = xmpTree.children.size(); schema != schemaLim; ++schema ) {
		const XMP_Node * currSchema = xmpTree.children[schema];
		SerializeCompactRDFElemProps ( currSchema, outputStr, newline, indentStr, baseIndent+3 );
	}


	for ( level = baseIndent+2; level > 0; --level ) outputStr += indentStr;
	outputStr += kRDF_SchemaEnd;
	outputStr += newline;

}
