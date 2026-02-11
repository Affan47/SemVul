MakeNewWorkspace( int j, int k, Type type )
{
  int level = GetLevel() + 1;
  if( level > expression_->GetHighestLevel() )
    expression_->SetHighestLevel( level );
  Workspace *aWs = new Workspace(level);
  aWs->SetType( type );
  aWs->SetExpression( expression_ );
  ExprCodes *aCode = new ExprCodes;
  aCode->SetOpeningBracket();
  aWs->GetCodes().push_back( aCode );
  for( int i=k+1; i<=j-1; ++i )
  {
    ExprCodes *e = new ExprCodes;
    aWs->GetCodes().push_back( e );
    *e = *codes_[i];
  }
  ExprCodes *bCode = new ExprCodes;
  bCode->SetClosingBracket();
  aWs->GetCodes().push_back( bCode );
  aWs->SetCodesAreParsed();
  expression_->AddWorkspace( aWs );
  codes_[k+1]->SetWorkspacePtr( aWs );
  for( std::size_t i=j+1; i<=codes_.size(); ++i )*codes_[i-j+k+1] = *codes_[i-1];
  for( int i=0; i<j-k-2; ++i )
  {
    delete codes_.back();
    codes_.pop_back();
  }
}
