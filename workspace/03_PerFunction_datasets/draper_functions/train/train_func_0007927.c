eql_i(VALUE key, VALUE val1, VALUE arg)
{
    struct equal_data *data = (struct equal_data *)arg;
    st_data_t val2;

    if (key == Qundef) return ST_CONTINUE;
    if (!st_lookup(data->tbl, key, &val2)) {
	data->result = Qfalse;
	return ST_STOP;
    }
    if (!(data->eql ? rb_eql(val1, (VALUE)val2) : (int)rb_equal(val1, (VALUE)val2))) {
	data->result = Qfalse;
	return ST_STOP;
    }
    return ST_CONTINUE;
}
