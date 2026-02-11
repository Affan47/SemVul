GetAttribute(const char* name) const {
    String v;
    if (style->find_attribute(name, v) || (
	    style->parent() == nil &&
	    World::current()->display()->style()->find_attribute(name, v)
	)
    ) {
	return v.string();
    }
    return nil;
}
