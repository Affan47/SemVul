callStackToString(const std::list<ErrorLogger::ErrorMessage::FileLocation> &callStack)
{
    std::ostringstream ostr;
    for (std::list<ErrorLogger::ErrorMessage::FileLocation>::const_iterator tok = callStack.begin(); tok != callStack.end(); ++tok)
        ostr << (tok == callStack.begin() ? "" : " -> ") << "[" << (*tok).getfile() << ":" << (*tok).line << "]";
    return ostr.str();
}
