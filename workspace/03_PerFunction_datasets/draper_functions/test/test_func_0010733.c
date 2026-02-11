incdec(std::string &value, const std::string &op)
{
    int ivalue = 0;
    std::istringstream istr(value.c_str());
    istr >> ivalue;
    if (op == "++")
        ++ivalue;
    else if (op == "--")
        --ivalue;
    std::ostringstream ostr;
    ostr << ivalue;
    value = ostr.str();
}
