open(const char *filename)
{

    this->filename = filename;
    ifstream::open(filename, ios::in);
    if  (ifstream::fail())
        return;
    delim = findDelimiter();
}
