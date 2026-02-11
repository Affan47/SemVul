check_equal_value(equal_val_array * array, double val)
{
    int i;


    if (array != NULL)
	for (i = 0; i < array->count; i++) {
	    if (array->values[i]->val == val) {
		array->values[i]->count++;
		G_debug(5, "found value %g with count %i at pos %i\n", val,
			array->values[i]->count, i);
		return 1;
	    }
	}


    add_equal_val_to_array(array, val);


    return 0;
}
