is_offset(struct ifd_entry *entry_ptr)
{
    if((value_type_size(entry_ptr->value_type) * entry_ptr->count) > 4)
        return(1);
    return(0);
}
