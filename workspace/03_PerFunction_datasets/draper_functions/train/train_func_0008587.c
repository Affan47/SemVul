addBorder(const Coord& pos)
{
    Ship* ship = get(pos).parent();
    if (ship) {
        Coord inc = ship->increment();
        Coord orth(inc.y, inc.x);
        Coord p = pos - inc;
        set(p, Element::BORDER);
        for (; p != pos + inc * (ship->size() + 1); p += inc) {
            set(p + orth, Element::BORDER);
            set(p - orth, Element::BORDER);
        }
        p -= inc;
        set(p, Element::BORDER);
    }
}
