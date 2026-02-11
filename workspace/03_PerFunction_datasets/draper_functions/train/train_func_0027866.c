returnsClasses() const
{
    TypePtr t = returnType();
    if(t && t->usesClasses())
    {
        return true;
    }
    ParamDeclList pdl = parameters();
    for(ParamDeclList::const_iterator i = pdl.begin(); i != pdl.end(); ++i)
    {
        if((*i)->isOutParam() && (*i)->type()->usesClasses())
        {
            return true;
        }
    }
    return false;
}
