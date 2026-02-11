set_alias(std::string name, std::string value, std::ostream &os) {
    AliasMap::iterator i = aliases.find (name) ;
    if (i != aliases.end()) {
        i->second = value ;
    } else {
        aliases[name] = value ;
    }
}
