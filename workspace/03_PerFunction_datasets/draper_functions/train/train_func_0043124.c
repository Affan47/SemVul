deleteUnit(Unit const &u) {
    if (u.abbr == _primary_unit[u.type]) {


	return false;
    }
    UnitMap::iterator iter = _unit_map.find(u.abbr);
    if (iter != _unit_map.end()) {
	delete (*iter).second;
	_unit_map.erase(iter);
	return true;
    } else {
	return false;
    }
}
