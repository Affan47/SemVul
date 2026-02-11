match_name(const UniqueString& name) {
    int match = 0;
    if (name_ != nil && name == *name_) {
	match = 1;
    } else if (aliases_ != nil) {
	int possible_match = 2;
	for (ListItr(UniqueStringList) i(*aliases_); i.more(); i.next()) {
	    if (name == *i.cur()) {
		match = possible_match;
		break;
	    }
	    ++possible_match;
	}
    }
    return match;
}
