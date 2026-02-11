invalidScanfFormatWidthError(const Token* tok, unsigned int numFormat, int width, const Variable *var)
{
    std::ostringstream errmsg;
    Severity::SeverityType severity = Severity::warning;
    bool inconclusive = false;

    if (var) {
        if (var->dimension(0) > width) {
            if (!_settings->inconclusive)
                return;
            inconclusive = true;
            errmsg << "Width " << width << " given in format string (no. " << numFormat << ") is smaller than destination buffer"
                   << " '" << var->name() << "[" << var->dimension(0) << "]'.";
        } else {
            errmsg << "Width " << width << " given in format string (no. " << numFormat << ") is larger than destination buffer '"
                   << var->name() << "[" << var->dimension(0) << "]', use %" << (var->dimension(0) - 1) << "s to prevent overflowing it.";
            severity = Severity::error;
        }

    } else
        errmsg << "Width " << width << " given in format string (no. " << numFormat << ") doesn't match destination buffer.";

    reportError(tok, severity, "invalidScanfFormatWidth", errmsg.str(), inconclusive);
}
