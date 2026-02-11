dump() const
{
	QString s = QString( "<step axis=\"%1\" nodetest=\"%2\">" ).arg( axisAsString( m_axis ) ).arg( m_nodeTest.string() );
	foreach( Predicate *predicate, m_predicates ) {
		s += predicate->dump();
	}
	s += "</step>";
	return s;
}
