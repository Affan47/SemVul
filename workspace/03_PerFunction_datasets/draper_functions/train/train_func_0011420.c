eval( ParseContext *_context ) const
{
  _context->type = ParseContext::T_DOUBLE;

  QVariant prop = _context->service->property( m_strId );
  if ( !prop.isValid() )
    return false;

  if ( !_context->initMaxima( m_strId ) )
    return false;

  QMap<QString,PreferencesMaxima>::Iterator it = _context->maxima.find( m_strId );
  if ( it == _context->maxima.end() )
    return false;

  if ( prop.type() == QVariant::Int && it.value().type == PreferencesMaxima::PM_INT )
  {
    _context->f = (double)( prop.toInt() - it.value().iMin ) /
                  (double)(it.value().iMax - it.value().iMin ) * (-2.0) + 1.0;
    return true;
  }
  else if ( prop.type() == QVariant::Double && it.value().type == PreferencesMaxima::PM_DOUBLE )
  {
    _context->f = ( prop.toDouble() - it.value().fMin ) / (it.value().fMax - it.value().fMin )
                  * (-2.0) + 1.0;
    return true;
  }

  return false;
}
