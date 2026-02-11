updateFromElement()
{
  DOM::NodeImpl *node = element();
  if ( node && (node->id() == ID_COL || node->id() == ID_COLGROUP) ) {
      DOM::HTMLTableColElementImpl *tc = static_cast<DOM::HTMLTableColElementImpl *>(node);
      m_span = tc->span();
  } else
      m_span = ! ( style() && style()->display() == TABLE_COLUMN_GROUP );
}
