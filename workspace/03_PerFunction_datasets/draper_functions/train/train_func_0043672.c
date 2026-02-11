setConsoleColor( TConsoleColor color,bool changeStdErr )
{
	static const int TS_NORMAL = 0;
	static const int TS_BLUE   = 1;
	static const int TS_GREEN  = 2;
	static const int TS_RED    = 4;
#ifdef MRPT_OS_WINDOWS
    static int normal_attributes = -1;
    HANDLE hstdout = GetStdHandle( changeStdErr ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );
	fflush(changeStdErr ? stderr: stdout);

    if( normal_attributes < 0 )
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo( hstdout, &info );
        normal_attributes = info.wAttributes;
    }

    SetConsoleTextAttribute( hstdout,
        (WORD)(color == TS_NORMAL ? normal_attributes :
        ((color & TS_BLUE ? FOREGROUND_BLUE : 0)|
        (color & TS_GREEN ? FOREGROUND_GREEN : 0)|
        (color & TS_RED ? FOREGROUND_RED : 0)|FOREGROUND_INTENSITY)) );
#else

    static const uint8_t ansi_tab[] = { 30, 34, 32, 36, 31, 35, 33, 37 };
    int code = 0;
	fflush( changeStdErr ? stdout:stderr );
    if( color != TS_NORMAL )
        code = ansi_tab[color & (TS_BLUE|TS_GREEN|TS_RED)];
    fprintf(changeStdErr ? stdout:stderr, "\x1b[%dm", code );
#endif
}
