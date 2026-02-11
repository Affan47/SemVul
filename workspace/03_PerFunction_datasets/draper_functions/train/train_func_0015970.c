has_info(const char* id) {
    std::string s(id);
    return (extra.find(s) != extra.end());
}
