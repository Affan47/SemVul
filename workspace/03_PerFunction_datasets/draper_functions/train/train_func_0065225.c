operator==(const ShadowData& o) const
{
    if ((next && !o.next) || (!next && o.next) ||
        (next && o.next && *next != *o.next))
        return false;

    return x == o.x && y == o.y && blur == o.blur && color == o.color;
}
