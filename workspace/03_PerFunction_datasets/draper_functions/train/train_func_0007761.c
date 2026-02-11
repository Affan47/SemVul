getValue(SArray &value, unsigned int chain,
			 bool (*condition)(Node const *)) const
{
    if (!(_range == value.range())) {
	string msg("Dimension mismatch when getting value of node array ");
	msg.append(name());
	throw runtime_error(msg);
    }

    unsigned int array_length = _range.length();
    vector<double> array_value(array_length);
    for (unsigned int j = 0; j < array_length; ++j) {
	Node const *node = _node_pointers[j];
	if (node && condition(node)) {
	    array_value[j] = node->value(chain)[_offsets[j]];
	}
	else {
	    array_value[j] = JAGS_NA;
	}
    }

    value.setValue(array_value);
}
