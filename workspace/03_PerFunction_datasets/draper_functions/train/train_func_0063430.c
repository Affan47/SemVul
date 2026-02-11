set_mime_not_modified(ostream &strm)
{
    strm << "HTTP/1.0 304 NOT MODIFIED" << CRLF ;
    const time_t t = time(0);
    strm << "Date: " << rfc822_date(t).c_str() << CRLF ;
    strm << CRLF ;
}
