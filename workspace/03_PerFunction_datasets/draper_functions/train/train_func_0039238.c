hit(const Coord& pos)
{
    Element& e = get(pos);
    HitInfo::Type type = e.hit();
    Ship* ship = e.parent();

    HitInfo res(type);
    if (ship && !ship->alive())
    {
        m_ships--;
        res.shipDestroyed = ship;
        res.shipPos = find(ship);
    }

    return res;
}
