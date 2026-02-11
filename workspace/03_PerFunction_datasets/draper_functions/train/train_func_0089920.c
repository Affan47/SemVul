FillOut( wxString &str ) const
{
  Workspace *ws = new Workspace(str);
  try
  {
    ws->ParseAndCheck( true );
  }
  catch( EExpressionError &e )
  {
    delete ws;
    throw;
  }
  wxString s;
  bool foundTV = false;
  std::deque<ExprCodes*> &codes = ws->GetCodes();
  std::deque<ExprCodes*>::iterator end = codes.end();
  for( std::deque<ExprCodes*>::iterator i=codes.begin(); i!=end; ++i )
  {
    if( (*i)->IsaTVariable() )
    {
      NumericData *ia = 0;
      NumericData *ic = 0;
      s += wxT("(")+(*i)->GetTVarPtr()->GetString(ia,ic)+wxT(")");
      foundTV = true;
    }
    else if( (*i)->IsaFunction() )
    {
      s += (*i)->GetFcnPtr()->Name();
    }
    else if( (*i)->IsaNVariable() )
    {
      s += (*i)->GetNVarPtr()->GetName();
    }
    else if( (*i)->IsaTString() )
    {
      s += (*i)->GetTString();
    }
    else if( (*i)->IsaConstant() )
    {
      s += (*i)->GetConstantString();
    }
    else if( (*i)->IsaOperator() )
    {
      s += (*i)->GetOpPtr()->Name();
    }
    else if( (*i)->IsaOpeningBracket() )
    {
      s += '(';
    }
    else if( (*i)->IsaClosingBracket() )
    {
      s += ')';
    }
    else if( (*i)->IsaComma() )
    {
      s += ',';
    }
    else if( (*i)->IsaSemicolon() )
    {
      s += ';';
    }
    else if( (*i)->IsaHash() )
    {
      s += '#';
    }
    else if( (*i)->IsaAsterisk() )
    {
      s += '*';
    }
    else if( (*i)->IsaImmediateValue() )
    {
      s += (*i)->GetImmediateValue();
    }
  }
  str = s;
  delete ws;
  return foundTV;
}
