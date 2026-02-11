findType(const std::string & name) const
{
    std::list<Type*>::const_iterator it;

    for (it = definedTypes.begin(); it != definedTypes.end(); ++it) {
        if ((*it)->name() == name)
            return (*it);
    }
    return 0;
}
