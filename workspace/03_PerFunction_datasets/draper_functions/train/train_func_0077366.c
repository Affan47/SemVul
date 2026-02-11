eval( ParseContext *_context ) const
{
  QVariant prop = _context->service->property( m_str );
  if ( !prop.isValid() )
    return false;

  if ( prop.type() == QVariant::String )
  {
    _context->str = prop.toString();
    _context->type = ParseContext::T_STRING;
    return true;
  }

  if ( prop.type() == QVariant::Int )
  {
    _context->i = prop.toInt();
    _context->type = ParseContext::T_NUM;
    return true;
  }

  if ( prop.type() == QVariant::Bool )
  {
    _context->b = prop.toBool();
    _context->type = ParseContext::T_BOOL;
    return true;
  }

  if ( prop.type() == QVariant::Double )
  {
    _context->f = prop.toDouble();
    _context->type = ParseContext::T_DOUBLE;
    return true;
  }

  if ( prop.type() == QVariant::List )
  {
    _context->seq = prop.toList();
    _context->type = ParseContext::T_SEQ;
    return true;
  }

  if ( prop.type() == QVariant::StringList )
  {
    _context->strSeq = prop.toStringList();
    _context->type = ParseContext::T_STR_SEQ;
    return true;
  }


  return false;
}
