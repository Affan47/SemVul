interpolate_dict_num(PermString name, Dict the_dict, bool force_integer)
{
    Type1Definition *def = dict(the_dict, name);
    Type1Definition *blend_def = dict(the_dict + dBlend, name);
    NumVector blend;

    if (def && blend_def && blend_def->value_numvec(blend)) {
	int n = _nmasters;
	double val = 0;
	for (int m = 0; m < n; m++)
	    val += blend[m] * _weight_vector[m];
	if (force_integer)
	    val = floor(val + 0.50001);
	def->set_num(val);
	kill_def(blend_def, the_dict + dBlend);
    } else if (def && !blend_def && force_integer) {
	double val;
	if (def->value_num(val))
	    def->set_num(floor(val + 0.50001));
    }
}
