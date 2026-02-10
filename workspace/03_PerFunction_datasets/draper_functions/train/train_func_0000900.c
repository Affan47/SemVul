add(const string& name, awt_mask_item *item) {
    awt_mask_item *existing = lookup(name);
    if (existing) return GB_export_errorf("ID '%s' already exists", name.c_str());

    id[name] = item;
    return 0;
}
