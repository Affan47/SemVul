context_message(int element_no, const char* message) const
{
    Element* e = _elements[element_no];
    StringAccum sa;
    if (e->landmark())
	sa << e->landmark() << ": ";
    sa << message << " '" << e->declaration() << "':";
    return sa.take_string();
}
