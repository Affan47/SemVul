db_changed()
{
    GB_ERROR error = 0;
    awt_assert(script);
    string current_value = script->get_value();
    error                = awt_mask_awar_item::set_value(current_value);

    if (error) aw_message(error);
}
