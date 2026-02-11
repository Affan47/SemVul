tokenData(char next)
{
    switch (next)
    {
	case '<':
	    m_token = TOKEN_TAG;
	break;

	case '>':


	break;

	default:
	    m_data.top() += next;
	break;
    }
}
