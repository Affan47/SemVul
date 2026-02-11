setBottom( CSSPrimitiveValueImpl *bottom )
{
    if( bottom ) bottom->ref();
    if ( m_bottom ) m_bottom->deref();
    m_bottom = bottom;
}
