GetName( tAccessLevel level )
{
    std::ostringstream s;
    s << "$config_accesslevel_" << level;
    return tString( tOutput( s.str().c_str() ) );
}
