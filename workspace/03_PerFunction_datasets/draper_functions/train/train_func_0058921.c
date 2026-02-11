username_completion_proc_call(VALUE self, VALUE str)
{
    VALUE result;
    char **matches;
    int i;

    matches = rl_completion_matches(StringValuePtr(str),
				    rl_username_completion_function);
    if (matches) {
	result = rb_ary_new();
	for (i = 0; matches[i]; i++) {
	    rb_ary_push(result, rb_locale_str_new_cstr(matches[i]));
	    free(matches[i]);
	}
	free(matches);
	if (RARRAY_LEN(result) >= 2)
	    rb_ary_shift(result);
    }
    else {
	result = Qnil;
    }
    return result;
}
