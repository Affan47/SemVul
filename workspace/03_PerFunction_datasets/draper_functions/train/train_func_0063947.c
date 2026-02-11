getFunction( const DOM::DOMString& name,
                                        const QList<Expression *> &args ) const
{
	if ( !m_functionDict.contains( name ) ) {
		kWarning() << "Function '" << name << "' not supported by this implementation.";

		return 0;
	}

	FunctionRec functionRec = m_functionDict[ name ];
	if ( !functionRec.args.contains( args.count() ) ) {
		kWarning() << "Function '" << name << "' requires " << functionRec.args.asString() << " arguments, but " << args.count() << " given.";
		return 0;
	}

	Function *function = functionRec.factoryFn();
	function->setArguments( args );
	function->setName( name );
	return function;
}

}
