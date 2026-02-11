antlr3RewriteRuleElementStreamNewAEE(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_RECOGNIZER rec, pANTLR3_UINT8 description, void * oneElement)
{
	pANTLR3_REWRITE_RULE_ELEMENT_STREAM	stream;


	stream	= antlr3RewriteRuleElementStreamNewAE(adaptor, rec, description);

	if (stream == NULL)
	{
		return NULL;
	}


	if	(oneElement != NULL)
	{
		stream->add(stream, oneElement, NULL);
	}
	return stream;
}
