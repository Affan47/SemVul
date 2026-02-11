isSlave() const
{
    string my_type;
    FWOptions *iface_opt = getOptionsObjectConst();
    if (iface_opt) my_type = iface_opt->getStr("type");
    Interface *parent = Interface::cast(getParent());
    return ((my_type.empty() || my_type == "ethernet") &&
            parent && parent->getOptionsObject()->getStr("type") == "bonding");
}
