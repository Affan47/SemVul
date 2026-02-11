AddFailure(std::ostream& os, DeferredTestResult const& result)
{
    os << ">";

    for (DeferredTestResult::FailureVec::const_iterator it = result.failures.begin();
         it != result.failures.end();
         ++it)
    {
        string const escapedMessage = XmlEscape(it->second);
        string const message = BuildFailureMessage(result.failureFile, it->first, escapedMessage);

        os << "<failure" << " message=\"" << message << "\"" << "/>";
    }
}
