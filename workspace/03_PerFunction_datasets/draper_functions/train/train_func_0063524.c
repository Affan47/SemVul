setUID(icalcomponent *comp, const std::string &uid)
{
    icalproperty *prop = icalcomponent_get_first_property(comp, ICAL_UID_PROPERTY);
    if (prop) {
        icalproperty_set_uid(prop, uid.c_str());
    } else {
        icalcomponent_add_property(comp, icalproperty_new_uid(uid.c_str()));
    }
}
