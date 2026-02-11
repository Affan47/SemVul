upd_minshowuid(Entry *ce, Section *cs ATTR_UNUSED)
{
    if (!ce->active) {
        ce->value = defminuid;
        ce->active = ce->written = True;
    }
}
