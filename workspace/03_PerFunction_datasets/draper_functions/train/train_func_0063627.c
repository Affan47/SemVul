checkPageContents(QPDFObjectHandle page,
                              std::string const& wanted_string)
{
    std::string contents = getPageContents(page);
    if (contents.find(wanted_string) == std::string::npos)
    {
        std::cout << "didn't find " << wanted_string << " in "
                  << contents << std::endl;
    }
}
