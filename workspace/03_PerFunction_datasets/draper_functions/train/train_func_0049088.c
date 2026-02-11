ExpandPath (const string &pth) {
    std::string path = pth;
    std::string::size_type p=path.find("~");
    if (p != string::npos) {
        std::string home;
        if (char *h = getenv("HOME"))
            home = h;
        path.replace(p, 1, home);
    }
    return path;
}
