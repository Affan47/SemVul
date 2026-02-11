nameEquals(const std::string& s) const {

    return (name() == s) || nameEquals(s.c_str());
}
