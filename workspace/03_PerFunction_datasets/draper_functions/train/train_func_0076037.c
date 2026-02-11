evaluateFile(Interpreter *interp, const char *fileName)
{
    UString code = readFile(fileName);
    if (code.isNull())
        return ErrorReadFile;

    return evaluateString(interp, fileName, code);
}
