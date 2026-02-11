parseDatum(unsigned otherAllowed,
			     ELObj *&result,
			     Location &loc,
			     Token &tok)
{
  if (!parseSelfEvaluating(otherAllowed|allowVector|allowUnquote|allowUnquoteSplicing, result, tok))
    return 0;
  loc = in_->currentLocation();
  if (result)
    return 1;
  switch (tok) {
  case tokenIdentifier:
    result = interp_->makeSymbol(currentToken_);
    break;
  case tokenQuote:
    return parseAbbreviation("quote", result);
  case tokenQuasiquote:
    return parseAbbreviation("quasiquote", result);
  case tokenUnquote:
    return parseAbbreviation("unquote", result);
  case tokenUnquoteSplicing:
    return parseAbbreviation("unquote-splicing", result);
  case tokenOpenParen:
    {
      ELObj *tem;
      Location ignore;
      if (!parseDatum(allowCloseParen, tem, ignore, tok))
	return 0;
      if (!tem) {
	result = interp_->makeNil();
	break;
      }
      ELObjDynamicRoot list(*interp_, tem);
      PairObj *last = new (*interp_) PairObj(tem, 0);
      list = last;
      for (;;) {
	if (!parseDatum(allowCloseParen|allowPeriod, tem, ignore, tok))
	  return 0;
	if (!tem) {
	  if (tok == tokenCloseParen) {
	    last->setCdr(interp_->makeNil());
	    break;
	  }
	  if (!parseDatum(0, tem, ignore, tok))
	    return 0;
	  last->setCdr(tem);
	  if (!getToken(allowCloseParen, tok))
	    return 0;
	  break;
	}
	last->setCdr(tem);
	PairObj *p = new (*interp_) PairObj(tem, 0);
	last->setCdr(p);
	last = p;
      }
      result = list;
    }
    break;
  case tokenVector:
    {
      VectorObj *v = new (*interp_) VectorObj;
      ELObjDynamicRoot protect(*interp_, v);
      Vector<ELObj *> &vec = *v;
      Location ignore;
      for (;;) {
	ELObj *tem;
	if (!parseDatum(allowCloseParen, tem, ignore, tok))
	  return 0;
	if (!tem)
	  break;
	vec.push_back(tem);
      }
      result = v;
    }
    break;
  default:
    break;
  }
  return 1;
}
