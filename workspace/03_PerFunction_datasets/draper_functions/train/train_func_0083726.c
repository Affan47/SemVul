DeleteChild( XMLNode* node )
{
    TIXMLASSERT( node->_parent == this );
    DELETE_NODE( node );
}
