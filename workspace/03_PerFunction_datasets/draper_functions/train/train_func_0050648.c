declaration() const
{
    StringAccum sa;
    sa << name() << " :: " << class_name();
    if (_ff.initialized())
	sa << '(' << _ff.print_filename() << ')';
    return sa.take_string();
}
