notify(Sea::Player player, const Coord& c, const HitInfo& info)
{
    foreach (Entity* entity, m_entities) {
        entity->notify(player, c, info);
        if (player == entity->player()) {
            entity->stats()->addInfo(info);
        }
    }
}
