hard_to_d() const {
    switch (u_.x.type) {
    case j_array:
    case j_object:
	return size();
    case j_bool:
    case j_int:
	return u_.i.x;
    case j_double:
        return u_.d.x;
    case j_null:
    case j_string:
    default:
        if (!u_.x.c)
            return 0;
        else
            return strtod(reinterpret_cast<const String&>(u_.str).c_str(), 0);
    }
}
