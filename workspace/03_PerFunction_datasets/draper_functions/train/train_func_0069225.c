AttributeIsSet(const char* name) const {
    String v;
    return (
	style->value_is_on(name) || (
	    style->parent() == nil && !style->find_attribute(name, v) &&
	    World::current()->display()->style()->value_is_on(name)
	)
    );
}
