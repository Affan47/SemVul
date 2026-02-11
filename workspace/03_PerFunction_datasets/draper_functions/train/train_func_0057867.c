remote_compiler_name() const
{
    if (job->compilerName().find("clang") != string::npos)
        return "clang";
    return job->language() == CompileJob::Lang_CXX ? "g++" : "gcc";
}
