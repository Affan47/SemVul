SaveLabel ( ostream& o ) const
{
	saveUInt(o,neMap.getI(const_cast<ClassifiableEntry*>(sample)));
	saveUInt(o,synonyms.size());
	for ( syn_iterator p = begin_syn(), p_end = end_syn(); p < p_end; ++p )
		saveUInt(o,neMap.getI(const_cast<ClassifiableEntry*>(*p)));
	o << "\n";
}
