complete_startup_info( KStartupInfoId& id, pid_t pid )
{
    if( X11_startup_notify_display == NULL )
        return;
    if( pid == 0 )
        KStartupInfo::sendFinishX( X11_startup_notify_display, id );
    else
    {
        KStartupInfoData data;
        data.addPid( pid );
        data.setHostname();
        KStartupInfo::sendChangeX( X11_startup_notify_display, id, data );
    }
    XCloseDisplay( X11_startup_notify_display );
    X11_startup_notify_display = NULL;
    X11_startup_notify_fd = -1;
}
