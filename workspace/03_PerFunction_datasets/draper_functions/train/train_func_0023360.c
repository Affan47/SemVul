find(const String &name, bool create)
{
    if (_sorted > 20)
	sort();

    if (_sorted == 100) {
	size_t l = 0, r = _names.size();
	while (l < r) {
	    size_t m = l + (r - l) / 2;
	    int cmp = String::compare(name, _names[m]);
	    if (cmp == 0)
		return _values.data() + value_size() * m;
	    else if (cmp < 0)
		r = m;
	    else
		l = m + 1;
	}
    } else {
	_sorted++;
	for (int i = 0; i < _names.size(); i++)
	    if (name == _names[i])
		return _values.data() + value_size() * i;
    }

    if (create && name) {
	_sorted = 0;
	_names.push_back(name);
	_values.extend(value_size());
	return _values.data() + _values.length() - value_size();
    } else
	return 0;
}
