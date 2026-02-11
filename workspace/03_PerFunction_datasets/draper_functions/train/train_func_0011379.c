isRecordTypeWithoutSideEffects(const Type* type)
{


    std::pair<std::map<const Type *,bool>::iterator,bool> found=isRecordTypeWithoutSideEffectsMap.insert(
                std::pair<const Type *,bool>(type,false));
    bool & withoutSideEffects=found.first->second;
    if (!found.second)
        return withoutSideEffects;

    if (type && type->classScope && type->classScope->numConstructors == 0 &&
        (type->classScope->varlist.empty() || type->needInitialization == Type::True)) {
        for (std::vector<Type::BaseInfo>::const_iterator i = type->derivedFrom.begin(); i != type->derivedFrom.end(); ++i) {
            if (!isRecordTypeWithoutSideEffects(i->type)) {
                withoutSideEffects=false;
                return withoutSideEffects;
            }
        }
        withoutSideEffects=true;
        return withoutSideEffects;
    }

    withoutSideEffects=false;
    return withoutSideEffects;
}
