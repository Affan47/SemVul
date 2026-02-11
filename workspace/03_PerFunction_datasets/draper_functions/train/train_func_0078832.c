replace(std::string &buffer,
        const std::string &pattern, const std::string &newstring)
{
    std::string::size_type pos = buffer.find(pattern);
    while (pos != std::string::npos) {
        buffer.replace(pos, pattern.size(), newstring);
        pos = buffer.find(pattern, pos + newstring.size());
    }
}
