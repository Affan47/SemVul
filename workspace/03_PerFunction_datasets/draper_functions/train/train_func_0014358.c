command_to_url( const COMMAND_ARGS& command )
{
    if( command.arg4 == "NEXT" ) return command.url + NEXT_SIGN + ARTICLE_SIGN + command.arg5;

    else if( command.arg4 == "LOG" ){

        if( command.url == URL_ALLLOG ) return URL_ALLLOG;
        else return command.url + LOG_SIGN;
    }

    else if( command.arg4 == "SIDEBAR" ){
        if( command.arg5.empty() ) return command.url;
        return command.url + SIDEBAR_SIGN + command.arg5;
    }

    return command.url;
}
