range_hash(Range *filt)
{
    return filt->include_lower | (filt->include_upper << 1)
        | ((sym_hash(filt->field)
            ^ (filt->lower_term ? str_hash(filt->lower_term) : 0)
            ^ (filt->upper_term ? str_hash(filt->upper_term) : 0)) << 2);
}
