icalcomponent_new_x (const char* x_name)
{
    icalcomponent* comp = icalcomponent_new_impl(ICAL_X_COMPONENT);
    if (!comp) {
       return 0;
    }
    comp->x_name = icalmemory_strdup(x_name);
    return comp;
}
