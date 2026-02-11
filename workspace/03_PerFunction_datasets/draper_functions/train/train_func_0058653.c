readDouble (double& val )
{
    Glib::ustring buf = readWord();
    double ival;
    if (getDouble(buf, &ival))
        val = ival;
    return *this;
}
