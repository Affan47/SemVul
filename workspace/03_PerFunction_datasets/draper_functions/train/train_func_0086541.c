available( const MapCoordinate& pos, ContainerBase* subject, int num )
{
    if ( !commandPending() ) {
        Vehicle* eht = actmap->getField(pos)->vehicle;
        if ( eht )
            if ( eht->color == actmap->actplayer * 8)
                return AttackCommand::avail ( eht );
    }
    return false;
}
