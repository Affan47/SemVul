hotswap_element() const
{
    if (Element *e = Element::hotswap_element())
	if (ToDump *td = (ToDump *)e->cast("ToDump"))
	    if (td->_filename == _filename
		&& td->_linktype == _linktype)
		return td;
    return 0;
}
