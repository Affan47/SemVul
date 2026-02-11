AddChild( DOMNode* node, IdentifierType i )
{
  if ( this->m_Children.size() == 0 )
    {
    this->AddChildAtEnd( node );
    return;
    }

  if ( node == NULL || this->ShareRoot(node) )
    {
    itkExceptionMacro( "not able to add child" );
    }

  if ( i < 0 || i >= static_cast<IdentifierType>(this->m_Children.size()) )
    {
    itkExceptionMacro( "not able to add child" );
    }

  node->m_Parent = this;
  this->m_Children.insert( this->m_Children.begin()+i, Pointer(node) );
}
