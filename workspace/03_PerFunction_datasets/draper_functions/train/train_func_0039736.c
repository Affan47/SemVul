get_member(const ObjectURI& uri, as_value* val)
	{
        as_object* proto = prototype();
        if (proto) return proto->get_member(uri, val);
        log_debug("Super has no associated prototype");
        return false;
	}
