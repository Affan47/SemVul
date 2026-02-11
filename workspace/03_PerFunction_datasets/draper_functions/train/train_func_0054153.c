refresh() {
    removeAll();
    if (fPath != null)
        loadMenus(fPath, this);
}
