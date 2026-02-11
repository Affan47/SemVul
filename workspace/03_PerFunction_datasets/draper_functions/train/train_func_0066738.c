exists() const
{
    std::string fullname = getName();
    return !access(fullname.c_str(), F_OK);
}
