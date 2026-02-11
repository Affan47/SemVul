Mouse_configure( const char * filename )
{
    struct stat statbuf;
    int fd, devmajor, devminor, is_mouse = 0;
    linux_mouse * mouse;
    unsigned char relcaps[(REL_MAX / 8) + 1];
    unsigned char abscaps[(ABS_MAX / 8) + 1];
    unsigned char keycaps[(KEY_MAX / 8) + 1];

    if( stat( filename, &statbuf ) == -1 )
        return;

    if( S_ISCHR( statbuf.st_mode ) == 0 )
        return;

    devmajor = ( statbuf.st_rdev & 0xFF00 ) >> 8;
    devminor = ( statbuf.st_rdev & 0x00FF );
    if ( ( devmajor != 13 ) || ( devminor < 64 ) || ( devminor > 96 ) )
        return;

    if( ( fd = open( filename, O_RDONLY | O_NONBLOCK ) ) < 0 )
        return;

    memset( relcaps, 0, sizeof( relcaps ) );
    memset( abscaps, 0, sizeof( abscaps ) );
    memset( keycaps, 0, sizeof( keycaps ) );


    if( ioctl( fd, EVIOCGBIT( EV_KEY, sizeof( keycaps ) ), keycaps ) == -1 )
        return;

    is_mouse = 0;
    if( ioctl( fd, EVIOCGBIT( EV_REL, sizeof( relcaps ) ), relcaps ) != -1 )
    {
        if( test_bit( relcaps, REL_X ) && test_bit( relcaps, REL_Y ) &&
            test_bit( keycaps, BTN_MOUSE ) )
        {
            is_mouse = 1;
        }

        if( test_bit( relcaps, REL_DIAL ) )
            is_mouse = 1;
    }

    if( ioctl( fd, EVIOCGBIT( EV_ABS, sizeof( abscaps ) ), abscaps ) != -1 )
    {
        if( test_bit( abscaps, ABS_X ) && test_bit( abscaps, ABS_Y ) &&
            ( test_bit( keycaps, BTN_MOUSE ) || test_bit( keycaps, BTN_TOUCH ) ) )
            is_mouse = 1;
    }

    if( !is_mouse )
        return;

    mouse = new linux_mouse;
    mouse->num = mice->size();
    ioctl( fd, EVIOCGNAME( CK_HID_NAMESIZE ), mouse->name );
    if( fd >= 0 )
        close( fd );
    strncpy( mouse->filename, filename, CK_HID_STRBUFSIZE );
    mice->push_back( mouse );
    EM_log( CK_LOG_INFO, "mouse: found device %s", mouse->name );
}
