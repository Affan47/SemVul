evaluateString(Interpreter *interp, const char *fileName,
                               const UString& code,
                               bool printResult = false)
{
    ExecState *exec = interp->globalExec();

    Completion res = interp->evaluate(fileName, 0, code);

    if (res.complType() == Throw) {
        CString msg = res.value()->toString(exec).UTF8String();
        JSObject* resObj = res.value()->toObject(exec);
        CString message = resObj->toString(exec).UTF8String();
        int line = resObj->toObject(exec)->get(exec, "line")->toUInt32(exec);

        if (fileName)
            fprintf(stderr, "%s (line %d): ", fileName, line);
        fprintf(stderr, "%s\n", msg.c_str());
        return ErrorEval;
    } else if (printResult) {
        if (res.isValueCompletion() && !res.value()->isUndefined()) {
            CString s8 = res.value()->toString(exec).UTF8String();
            if (s8.size() != 0)
                fprintf(stdout, "%s\n", s8.c_str());
        }
    }

    return ErrorNone;
}
