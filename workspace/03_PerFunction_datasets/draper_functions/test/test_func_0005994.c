print()
{
    std::cout << "size=" << alloctype.size() << std::endl;
    std::map<unsigned int, std::string>::const_iterator it;
    for (it = alloctype.begin(); it != alloctype.end(); ++it) {
        std::string strusage;
        std::map<unsigned int, std::string>::const_iterator use = possibleUsage.find(it->first);
        if (use != possibleUsage.end())
            strusage = use->second;

        std::cout << "alloctype='" << it->second << "' "
                  << "possibleUsage='" << strusage << "'" << std::endl;
    }
}
