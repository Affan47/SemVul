HandleCancelChanneling(WorldPacket& recv_data)
{
    recv_data.read_skip<uint32>();


    Unit* mover = _player->GetMover();
    if (mover != _player && mover->GetTypeId() == TYPEID_PLAYER)
        { return; }

    _player->InterruptSpell(CURRENT_CHANNELED_SPELL);
}
