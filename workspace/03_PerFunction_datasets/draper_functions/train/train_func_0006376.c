se_DisplayChatLocally( ePlayerNetID* p, const tString& say )
{
#ifdef DEBUG_X
    if (strstr( say, "BUG" ) )
    {
        st_Breakpoint();
    }
#endif

    if ( p && !p->IsSilenced() && se_enableChat )
    {


        tColoredString message;
        message << *p;
        message << tColoredString::ColorString(1,1,.5);
        message << ": " << say << '\n';

        con << message;
    }
}
