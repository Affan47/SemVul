countMinArgs(const Token* argList)
{
    if (!argList)
        return 0;

    argList = argList->next();
    if (argList->str() == ")")
        return 0;

    unsigned int count = 1;
    for (; argList; argList = argList->next()) {
        if (argList->link() && Token::Match(argList, "(|[|{|<"))
            argList = argList->link();
        else if (argList->str() == ",")
            count++;
        else if (argList->str() == "=")
            return count-1;
        else if (argList->str() == ")")
            break;
    }
    return count;
}
