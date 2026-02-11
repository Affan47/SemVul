set_mime_error(ostream &strm, int code, const string &reason,
               const string &version)
{
    strm << "HTTP/1.0 " << code << " " << reason.c_str() << CRLF ;
    if (version == "") {
        strm << "XDODS-Server: " << DVR << CRLF ;
        strm << "XOPeNDAP-Server: " << DVR << CRLF ;
    }
    else {
        strm << "XDODS-Server: " << version.c_str() << CRLF ;
        strm << "XOPeNDAP-Server: " << version.c_str() << CRLF ;
    }
    strm << "XDAP: " << DAP_PROTOCOL_VERSION << CRLF ;

    const time_t t = time(0);
    strm << "Date: " << rfc822_date(t).c_str() << CRLF ;
    strm << "Cache-Control: no-cache" << CRLF ;
    strm << CRLF ;
}
