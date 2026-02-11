reportErr(const std::string &errmsg)
{

    if (_errorList.find(errmsg) != _errorList.end())
        return;

    _errorList.insert(errmsg);
    std::cerr << errmsg << std::endl;
}
