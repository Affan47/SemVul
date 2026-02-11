AddConstant(const string& name, double value)
{
    if(isValidName(name))
    {
        const char* n = name.c_str();
        if(FindVariable(n, data->FuncParserNames) !=
           data->FuncParserNames.end() ||
           FindVariable(n, data->FuncPtrNames) !=
           data->FuncPtrNames.end())
            return false;

        copyOnWrite();

        data->Constants[name] = value;
        return true;
    }
    return false;
}
