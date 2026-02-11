EndTest(std::ostream& os, DeferredTestResult const& result)
{
    if (result.failed)
        os << "</test>";
    else
        os << "/>";
}
