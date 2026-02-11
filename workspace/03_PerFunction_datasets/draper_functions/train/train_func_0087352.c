doEvaluate() const
{
#ifdef XPATH_VERBOSE
	if ( m_absolute ) {
		kDebug(6011) << "Evaluating absolute path expression, steps:" << m_steps.count();
	} else {
		kDebug(6011) << "Evaluating relative path expression, steps:" << m_steps.count();
	}
#endif

	DomNodeList inDomNodes  = new StaticNodeListImpl,
	            outDomNodes;


	NodeImpl *context = Expression::evaluationContext().node;
	if ( m_absolute ) {
		if ( context->nodeType() != Node::DOCUMENT_NODE ) {
			context = context->ownerDocument();
		}
	}

	inDomNodes->append( context );

	if ( m_steps.isEmpty() )
		return Value( inDomNodes );

	int s = 0;
	foreach( Step *step, m_steps ) {
#ifdef XPATH_VERBOSE
		kDebug(6011) << "-------------------------------------";
		kDebug(6011) << "Step " << s << "insize " << inDomNodes->length();
#endif

		outDomNodes = new StaticNodeListImpl;
		for ( unsigned long i = 0; i < inDomNodes->length(); ++i ) {
			DomNodeList matches = step->evaluate( inDomNodes->item( i ) );
			for ( unsigned long j = 0; j < matches->length(); ++j )
				outDomNodes->append( matches->item( j ) );
		}
		inDomNodes = outDomNodes;

		++s;
	}

#ifdef XPATH_VERBOSE
	kDebug(6011) << "-------------------------------------";
	kDebug(6011) << "output:" <<outDomNodes->length();
	kDebug(6011) << "=====================================";
#endif

	return Value( outDomNodes );
}
