delProperty(const ObjectURI& uri)
{

	iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found == _props.end()) {
		return std::make_pair(false, false);
	}


	if (found->getFlags().test<PropFlags::dontDelete>()) {
		return std::make_pair(true, false);
	}

	_props.erase(found);
	return std::make_pair(true, true);
}
