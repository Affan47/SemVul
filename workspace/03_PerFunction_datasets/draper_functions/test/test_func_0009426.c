parse_hostname_chrome_compatible(std::string& project_url, std::string& hostname) {
    std::basic_string<char>::size_type start;
    std::basic_string<char>::size_type end;

    start = project_url.find("//", 0) + 2;
    end   = project_url.find("/", start);

    hostname = project_url.substr(start, end - start);

    if (starts_with(hostname.c_str(), "www"))
        hostname.erase(0, 3);

    if (!hostname.empty())
        return true;

    return false;
}
