declareFunction(Funcao& f) {

  if(evalVariableRedeclaration(SymbolTable::GlobalScope, f.id)) {
    return;
  }

  Symbol sfunc(SymbolTable::GlobalScope, f.id->getText(), f.id->getLine(), true, f.return_type.primitiveType(), f.return_type.dimensions());

	list< pair<RefPortugolAST, SymbolType> >::iterator it = f.params.begin();
	for( ; it != f.params.end(); ++it) {
		if((*it).second.isPrimitive()) {
			sfunc.param.add((*it).first->getText(), (*it).second.primitiveType());
			declareVar((*it).second.primitiveType(), (*it).first);
		} else {
			sfunc.param.add((*it).first->getText(),(*it).second);
			declareVar((*it).second.primitiveType(), (*it).second.dimensions(), (*it).first);
		}
	}

  stable.insertSymbol(sfunc, SymbolTable::GlobalScope);
}
