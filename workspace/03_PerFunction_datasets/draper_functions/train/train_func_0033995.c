set_dict_size(int d, int size)
{
    Type1Item *item = dict_size_item(d);
    if (!item)
	return;
    if (Type1Definition *t1d = item->cast_definition()) {
	int num;
	if (strstr(t1d->definer().c_str(), "dict") && t1d->value_int(num))
	    t1d->set_int(size);
    } else if (Type1CopyItem *copy = item->cast_copy()) {
	String value = copy->value();
	int pos = value.find_left(" dict");
	if (pos >= 1 && isdigit((unsigned char) value[pos - 1])) {
	    int numpos = pos - 1;
	    while (numpos >= 1 && isdigit((unsigned char) value[numpos - 1]))
		numpos--;
	    StringAccum accum;
	    accum << value.substring(0, numpos) << size << value.substring(pos);
	    copy->set_value(accum.take_string());
	}
    }
}
