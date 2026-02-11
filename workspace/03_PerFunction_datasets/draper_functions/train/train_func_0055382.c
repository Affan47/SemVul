doDeclareFlowObjectMacro()
{
  Location loc(in_->currentLocation());
  Token tok;
  if (!getToken(allowIdentifier, tok))
    return 0;
  Identifier *ident = lookup(currentToken_);
  if (ident->flowObj())

    ;
  if (!getToken(allowOpenParen, tok))
    return 0;
  Vector<const Identifier *> nics;
  NCVector<Owner<Expression> > inits;
  const Identifier *contentsId = 0;
  unsigned allowed = (allowOpenParen|allowCloseParen|allowIdentifier|allowHashContents);
  for (;;) {
    if (!getToken(allowed, tok))
      return 0;
    if (tok == tokenCloseParen)
      break;
    switch (tok) {
    case tokenHashContents:
      if (!getToken(allowIdentifier, tok))
	return 0;
      contentsId = lookup(currentToken_);
      allowed = allowCloseParen;
      break;
    case tokenIdentifier:
      nics.push_back(lookup(currentToken_));
      break;
    case tokenOpenParen:
      {
	if (!getToken(allowIdentifier, tok))
	  return 0;
	nics.push_back(lookup(currentToken_));
	inits.resize(nics.size());
	Identifier::SyntacticKey key;
	if (!parseExpression(0, inits.back(), key, tok))
	  return 0;
	if (!getToken(allowCloseParen, tok))
	  return 0;
      }
      break;
    default:
      CANNOT_HAPPEN();
    }
  }

  Owner<Expression> body;
  Identifier::SyntacticKey key;
  if (!parseExpression(0, body, key, tok))
    return 0;
  if (!getToken(allowCloseParen, tok))
    return 0;
  Location defLoc;
  unsigned defPart;
  if (ident->inheritedCDefined(defPart, defLoc)
      && defPart <= interp_->currentPartIndex()) {
    if (defPart == interp_->currentPartIndex()) {
      interp_->setNextLocation(loc);
      interp_->message(InterpreterMessages::duplicateFlowObjectClass,
		       StringMessageArg(ident->name()),
		       defLoc);
    }
  }
  else {
    MacroFlowObj *flowObj
      = new (*interp_) MacroFlowObj(nics, inits, contentsId, body);
    interp_->makePermanent(flowObj);
    ident->setFlowObj(flowObj);
  }
  return 1;
}
