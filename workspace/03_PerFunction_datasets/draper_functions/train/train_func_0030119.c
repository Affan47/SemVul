update ()
{
    static double tenth_minute = gametime::minute () / 10.0;


    Ticks += gametime::frames_to_skip ();


    while (Ticks >= tenth_minute)
    {
        Ticks -= tenth_minute;
        Time++;


        time_event evt (Time);
        event_handler::raise_event (&evt);
    }
}
