call_selected(int fd, int mask) const
{
    if ((unsigned) fd < (unsigned) _element_selectors.size()) {
	const ElementSelector &es = _element_selectors[fd];
	Element *read = (mask & Element::SELECT_READ ? es.read : 0);
	Element *write = (mask & Element::SELECT_WRITE ? es.write : 0);
	if (read)
	    read->selected(fd, write == read ? mask : Element::SELECT_READ);
	if (write && write != read)
	    write->selected(fd, Element::SELECT_WRITE);
    }
}
