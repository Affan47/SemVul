eval( ParseContext *_context ) const
{
  ParseContext c1( _context );
  ParseContext c2( _context );


  if ( !m_pLeft->eval( &c1 ) )
    return false;

  if ( c1.type != ParseContext::T_BOOL )
    return false;

  _context->b = c1.b;
  _context->type = ParseContext::T_BOOL;
  if ( c1.b )
    return true;

  if ( !m_pRight->eval( &c2 ) )
    return false;

  if ( c2.type != ParseContext::T_BOOL )
    return false;

  _context->b = ( c1.b || c2.b );
  _context->type = ParseContext::T_BOOL;

  return true;
}
