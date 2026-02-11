fallback(ThemeItem_base &item) {
    if (item.name() == "menu.borderWidth") {
        return ThemeManager::instance().loadItem(item, "borderWidth", "BorderWidth");
    } else if (item.name() == "menu.borderColor") {
        return ThemeManager::instance().loadItem(item, "borderColor", "BorderColor");
    } else if (item.name() == "menu.bevelWidth") {
        return ThemeManager::instance().loadItem(item, "bevelWidth", "BevelWidth");
    }

    return false;
}
