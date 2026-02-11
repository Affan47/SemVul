operator<<(libkeyer::Keyer& out, const Koch& exc)
{
    std::list<std::string> lks = exc.tokenize();
    typedef std::list< std::string >::const_iterator c_str;

    for(c_str lks_it = lks.begin(); lks_it != lks.end(); lks_it++)
	out << *lks_it;

    return out;
}
