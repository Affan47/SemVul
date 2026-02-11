do_break( const int point )
{
    if (point == -1)
    {
        list_breakpoints();
        return;
    }
    if ( max_break < max_breaks - 1 )
    {
        breakpoints[ max_break++ ] = point;
        cout << hex
             << "Breakpoint set at 0x" << setw( 4 )
             << setfill( '0' ) << point << endl;
        list_breakpoints();
    }
    else
        cout << "Maximum breakpoints already set...\n";
}
