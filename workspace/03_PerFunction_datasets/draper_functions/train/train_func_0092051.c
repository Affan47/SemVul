addMediaDevice( QString uid, QString username )
{
    MediaDeviceSettings s;
    s.beginGroup( uid );
    s.setValue( "user", username );
    s.sync();
}
