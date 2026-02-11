addItem(const ustring &name, int hotCharPos, YAction *action, YMenu *submenu) {
    return add(new YMenuItem(name, hotCharPos, null, action, submenu));
}
