remove(const string& name) {
    if (!lookup(name)) return GB_export_errorf("ID '%s' does not exist", name.c_str());
    id.erase(name);
    return 0;
}
