forceHit(const Coord& pos, const HitInfo& info)
{
    switch (info.type) {
    case HitInfo::HIT:
        get(pos).setType(Element::DEAD);
        if (info.shipDestroyed) {
            Coord c = info.shipPos;
            for (unsigned int i = 0; i < info.shipDestroyed->size(); i++) {
                get(c).setParent(info.shipDestroyed);
                c += info.shipDestroyed->increment();
            }
            m_ships--;
        }
        break;
    case HitInfo::MISS:
        get(pos).setType(Element::MISS);
        break;
    case HitInfo::INVALID:
        break;
    }
}
