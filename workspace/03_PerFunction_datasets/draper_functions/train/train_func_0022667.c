incorporate(match *other) {
	for(map<int,term*>::iterator i = other->parameters.begin(); i!=other->parameters.end(); i++) {
		parameters[i->first] = i->second;
	}

	for(map<term*,term*>::iterator i = other->mapping.begin(); i!=other->mapping.end(); i++) {
		mapping[i->first] = i->second;
	}

	for(map<name,name>::iterator i = other->names.begin(); i!=other->names.end(); i++) {
		capture_name(i->first,i->second);
	}

}
