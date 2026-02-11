printUndefinedMembers (std::ostream &os) {
    os << "\tundefined members:" ;
    Scope::VarMap::iterator i = variables.begin() ;
    for (; i != variables.end() ; i++) {
        if (i->first[0] == '.') {
            Tag *tag = (Tag*)i->second ;
            if (tag->flags & VAR_PREDEFINED) {
                os << "\n\t\t" << tag->block->name ;
            }
        }

    }
}
