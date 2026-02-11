wrongPrintfScanfArgumentsError(const Token* tok,
        const std::string &functionName,
        unsigned int numFormat,
        unsigned int numFunction)
{
    Severity::SeverityType severity = numFormat > numFunction ? Severity::error : Severity::warning;
    if (severity != Severity::error && !_settings->isEnabled("style"))
        return;

    std::ostringstream errmsg;
    errmsg << functionName
           << " format string requires "
           << numFormat
           << " parameter" << (numFormat != 1 ? "s" : "") << " but "
           << (numFormat > numFunction ? "only " : "")
           << numFunction
           << (numFunction != 1 ? " are" : " is")
           << " given.";

    reportError(tok, severity, "wrongPrintfScanfArgNum", errmsg.str());
}
