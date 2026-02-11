insert(MenuItem *item, int pos) {
    if (pos == -1) {
        menuitems.push_back(item);
    } else {
        menuitems.insert(menuitems.begin() + pos, item);
    }
    m_need_update = true;
    return menuitems.size();
}
