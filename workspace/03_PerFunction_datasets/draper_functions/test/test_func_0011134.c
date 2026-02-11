shift_i_safe(VALUE key, VALUE value, VALUE arg)
{
    struct shift_var *var = (struct shift_var *)arg;

    if (key == Qundef) return ST_CONTINUE;
    var->key = key;
    var->val = value;
    return ST_STOP;
}
