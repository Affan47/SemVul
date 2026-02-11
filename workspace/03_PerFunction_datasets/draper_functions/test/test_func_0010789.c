countTokens()
{
    StreamGuard guard(stream, offset);


    std::streamoff curroff = offset;


    offset = offend;

    int count = 0;
    while (hasMoreTokens()) {
	nextToken();
	count++;
    }


    offset = curroff;

    return count;
}
