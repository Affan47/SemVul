checkDuplInheritedMembers()
{
    if (!_settings->isEnabled("warning"))
        return;


    for (std::list<Type>::const_iterator classIt = symbolDatabase->typeList.begin();
         classIt != symbolDatabase->typeList.end();
         ++classIt) {

        for (std::vector<Type::BaseInfo>::const_iterator parentClassIt = classIt->derivedFrom.begin();
             parentClassIt != classIt->derivedFrom.end();
             ++parentClassIt) {

            if (!parentClassIt->type || !parentClassIt->type->classScope)
                continue;

            for (std::list<Variable>::const_iterator classVarIt = classIt->classScope->varlist.begin();
                 classVarIt != classIt->classScope->varlist.end();
                 ++classVarIt) {
                for (std::list<Variable>::const_iterator parentClassVarIt = parentClassIt->type->classScope->varlist.begin();
                     parentClassVarIt != parentClassIt->type->classScope->varlist.end();
                     ++parentClassVarIt) {
                    if (classVarIt->name() == parentClassVarIt->name() && !parentClassVarIt->isPrivate()) {
                        duplInheritedMembersError(classVarIt->nameToken(), parentClassVarIt->nameToken(),
                                                  classIt->name(), parentClassIt->type->name(), classVarIt->name(),
                                                  classIt->classScope->type == Scope::eStruct,
                                                  parentClassIt->type->classScope->type == Scope::eStruct);
                    }
                }
            }
        }
    }
}
