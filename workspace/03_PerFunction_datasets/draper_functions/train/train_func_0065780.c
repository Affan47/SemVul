toString() const
{
    std::string str;
    std::vector<Suggestion>::const_iterator i;
    for( i=suggestions.begin(); i!=suggestions.end(); i++ ) {
	str += i->toString();
    }
    return str;
}
