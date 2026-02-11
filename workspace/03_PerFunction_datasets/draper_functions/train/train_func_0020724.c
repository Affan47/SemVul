print( std::ostream& ostr ) const
{

    for ( const_map_iterator m = map_begin(); m != map_end(); ++m )
    {
	ostr << "(" << m->first << "," << m_weights[m->second] << ") ";
    }
    ostr << std::endl;
}
