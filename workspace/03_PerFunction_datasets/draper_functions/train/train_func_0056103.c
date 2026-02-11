Joystick_quit()
{
    if( joysticks == NULL )
        return;

    vector< linux_joystick * >::size_type i, len = joysticks->size();

    for( i = 0; i < len; i++ )
        delete joysticks->at( i );

    delete joysticks;
    joysticks = NULL;
}
