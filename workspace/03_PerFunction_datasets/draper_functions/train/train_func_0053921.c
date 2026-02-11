PushHistory( const std::string &app,
                                  const std::string &message )

{
#define MY_MIN(a,b)      ((a<b) ? a : b)

    char current_time[17];
    char history[81];

    GetCurrentDateTime( current_time );

    memset( history, ' ', 80 );
    history[80] = '\0';

    memcpy( history + 0, app.c_str(), MY_MIN(app.size(),7) );
    history[7] = ':';

    memcpy( history + 8, message.c_str(), MY_MIN(message.size(),56) );
    memcpy( history + 64, current_time, 16 );

    std::vector<std::string> history_entries = GetHistoryEntries();

    history_entries.insert( history_entries.begin(), history );
    history_entries.resize(8);

    SetHistoryEntries( history_entries );
}
