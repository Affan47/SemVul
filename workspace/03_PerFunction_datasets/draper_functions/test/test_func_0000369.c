close()
{
    if( !this->valid() )
        return;

    _data->slot().onDisconnect( *this );


    _data->setValid(false);
    _data->sender().onConnectionClose( *this );
}
