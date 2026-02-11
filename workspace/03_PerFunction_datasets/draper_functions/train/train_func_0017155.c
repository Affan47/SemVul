assignOther( const Node &other, int elementId )
{
    if (other.elementId() != static_cast<quint32>(elementId)) {
	if ( impl ) impl->deref();
	impl = 0;
    } else {
	Node::operator = (other);
    }
}
