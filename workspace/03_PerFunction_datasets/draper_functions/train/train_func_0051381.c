evaluateInteractive(Interpreter *interp)
{
    char *line;
    while ((line = readLine("JS> ")) != 0) {
        UString code(line);
        free(line);
        evaluateString(interp, 0, code, true);
    }

    return ErrorNone;
}
