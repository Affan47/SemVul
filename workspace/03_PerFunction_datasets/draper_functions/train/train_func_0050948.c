operator()(FunctionPtr const &func, string const &name) const
    {
	if (LINK(func))
	    return LINK(func)->name() == name;
	if (SCALAR(func))
	    return SCALAR(func)->name() == name;
	if (VECTOR(func))
	    return VECTOR(func)->name() == name;
	if (ARRAY(func))
	    return ARRAY(func)->name() == name;

	return false;
    }
}
