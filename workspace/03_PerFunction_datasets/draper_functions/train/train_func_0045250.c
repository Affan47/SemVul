findDelimiter()
{
    ifstream in;
    int type = 0;

    in.open(filename.c_str(), ios::in);
    if (in.fail())
        return delim;

    in.seekg(0, ios::beg);


    if (in.is_open()) {
        char c;
        while (in.get(c)) {
            if (c == CR)
                type |= 1;
            else if (c == LF)
                type |= 2;
            else if (type)
                break;
        }
    }
    in.close();

    switch (type) {
	case 1:

	    delim = '\r';
	    break;
	case 2:

	    delim = '\n';
	    break;
	case 3:

	    delim = '\n';
	    break;
	default:

	    delim = '\n';
    }
    return delim;
}
