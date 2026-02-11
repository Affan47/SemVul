textMatch(xml_iterator& it, const xml_iterator end,
        const std::string& match, bool advance)
{
    const std::string::size_type len = match.length();

    if (static_cast<size_t>(end - it) < len) return false;

    if (!std::equal(it, it + len, match.begin(), boost::is_iequal())) {
        return false;
    }
    if (advance) it += len;
    return true;
}
