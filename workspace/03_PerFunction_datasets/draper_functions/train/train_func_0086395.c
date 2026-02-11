showOnce( QWidget *parent )
{
    DEBUG_BLOCK

    if( s_instance == 0 )
        s_instance = new EqualizerDialog( parent );

    s_instance->activateWindow();
    s_instance->show();
    s_instance->raise();
    s_instance->storeOriginalSettings();
}
