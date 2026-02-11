nodeIndex() const
{
    NodeImpl *_tempNode = previousSibling();
    unsigned long count=0;
    for( count=0; _tempNode; count++ )
        _tempNode = _tempNode->previousSibling();
    return count;
}
