dumpModules()
{


    std::cerr << _modules.size() << " plugin(s) for Gnash installed" << std::endl;
    std::vector<std::string>::iterator it;
    for (it = _modules.begin(); it != _modules.end(); ++it) {
        std::cerr << "Module name is: \"" << *(it) << "\"" << std::endl;
    }
}

}
