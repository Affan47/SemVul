beginMember(const std::string& name)
{
    log_trace("beginMember(\"" << name << ')');
    *_out << '\1';
}
