tagHook (struct dom_data *data, char *name, char **atts, int type)
{
	iks *x;

	if (IKS_OPEN == type || IKS_SINGLE == type) {
		if (data->current) {
			x = iks_insert (data->current, name);
		} else {
			ikstack *s;
			s = iks_stack_new (data->chunk_size, data->chunk_size);
			x = iks_new_within (name, s);
		}
		if (atts) {
			int i=0;
			while (atts[i]) {
				iks_insert_attrib (x, atts[i], atts[i+1]);
				i += 2;
			}
		}
		data->current = x;
	}
	if (IKS_CLOSE == type || IKS_SINGLE == type) {
		x = iks_parent (data->current);
		if (iks_strcmp(iks_name(data->current), name) != 0)
			return IKS_BADXML;
		if (x)
			data->current = x;
		else {
			*(data->iksptr) = data->current;
			data->current = NULL;
		}
	}
	return IKS_OK;
}
