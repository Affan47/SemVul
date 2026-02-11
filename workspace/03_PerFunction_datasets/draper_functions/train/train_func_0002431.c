value_inc( Value *value )
{
    *value->val_int += value->step;
    if ( *value->val_int > value->max ) *value->val_int = value->min;
    value_update_str( value );
}
