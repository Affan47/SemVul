poll(bool can_read)
{
    if (!can_read) return;

    m_socket.peek();

    std::streamsize count;

    if ((count = m_socket.rdbuf()->in_avail()) > 0) {

        for (int i = 0; i < count; ++i) {

	    int next = m_socket.rdbuf()->sbumpc();


            switch(next)
            {
            case '#':
                if(!stringmode())
                {
                    m_state.push(PARSE_COMMENT);
                    continue;
                }
                break;

            case '\n':
	        m_linenum++;
                if(!stringmode())
                    continue;
                break;
            case '\r':
                continue;
            default:
                break;
            }

            switch (m_state.top())
	    {
            case PARSE_INIT:       parseInit(next); break;
            case PARSE_STREAM:     parseStream(next); break;
            case PARSE_MAP:        parseMap(next); break;
            case PARSE_LIST:       parseList(next); break;
            case PARSE_DATA:       parseData(next); break;
            case PARSE_INT:	       parseInt(next); break;
            case PARSE_FLOAT:      parseFloat(next); break;
            case PARSE_STRING:     parseString(next); break;
	    case PARSE_LITERAL:    parseLiteral(next); break;
            case PARSE_NAME:       parseName(next); break;
	    case PARSE_COMMENT:    parseComment(next); break;
	    }
        }
    }
}
