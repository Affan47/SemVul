subscribe(Event::Group group, const Event::Subscriber& slot)
{
    Event::Connection c(new BoundSlot(group, slot, *this));
    d_slots.insert(std::pair<Group, Connection>(group, c));
    return c;
}
