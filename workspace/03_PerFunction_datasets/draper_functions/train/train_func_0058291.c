dirname(const std::string& path)
    {
        if (path == "") return ".";

        std::string p = path;
        while (   p.length() > 1
               && (p[p.length()-1] == '\\' || p[p.length()-1] == '/')) {
            p = p.substr(0, p.length()-1);
        }
        if (p == "\\" || p == "/") return p;
        if (p.length() == 2 && p[1] == ':') return p;
        std::string::size_type idx = p.find_last_of("\\/");
        if (idx == std::string::npos) return ".";
        if (idx == 1 && p[0] == '\\' && p[1] == '\\') return p;
        p = p.substr(0, idx == 0 ? 1 : idx);
        while (   p.length() > 1
               && (p[p.length()-1] == '\\' || p[p.length()-1] == '/')) {
            p = p.substr(0, p.length()-1);
        }
        return p;
    }
