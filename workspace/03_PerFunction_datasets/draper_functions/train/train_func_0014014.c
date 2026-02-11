HandlePlayerKillInsideArea(Player* player)
{
    for (uint8 i = 0; i < MAX_ZM_TOWERS; ++i)
    {
        if (GameObject* capturePoint = player->GetMap()->GetGameObject(m_towerBanners[i]))
        {

            GameObjectInfo const* info = capturePoint->GetGOInfo();
            if (info && player->IsWithinDistInMap(capturePoint, info->capturePoint.radius))
            {

                if (player->GetTeam() == m_towerOwner[i])
                    player->CastSpell(player, player->GetTeam() == ALLIANCE ? SPELL_ZANGA_TOWER_TOKEN_ALLIANCE : SPELL_ZANGA_TOWER_TOKEN_HORDE, true);

                return;
            }
        }
    }
}
