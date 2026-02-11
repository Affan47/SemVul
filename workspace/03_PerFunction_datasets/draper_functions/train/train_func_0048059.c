set_mime_ddx_boundary(ostream &strm, const string &boundary,
	const string &cid, ObjectType type, EncodingType enc)
{
    strm << "--" << boundary << CRLF;
    strm << "Content-Type: Text/xml; charset=iso-8859-1" << CRLF;
    strm << "Content-Id: <" << cid << ">" << CRLF;
    strm << "Content-Description: " << descrip[type] << CRLF ;
    if (enc != x_plain)
         strm << "Content-Encoding: " << encoding[enc] << CRLF ;

    strm << CRLF;
}
