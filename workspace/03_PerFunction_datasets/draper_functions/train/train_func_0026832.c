cycleItems(bool reverse) {
    Menuitems vec;
    if (m_type_ahead.stringSize())
        vec = m_matches;
    else
        vec = menuitems;

    if (vec.size() < 1)
        return;


    int new_index = -1;
    bool passed = !validIndex(m_active_index);
    for (size_t i = 0; i < vec.size(); i++) {
        if (!isItemSelectable(vec[i]->getIndex()) ||
            vec[i]->getIndex() == m_active_index)
            continue;


        if (!passed && vec[i]->getIndex() > m_active_index) {
            if (reverse && new_index != -1)
                break;
            passed = true;
        }


        if (passed && !reverse) {
            new_index = vec[i]->getIndex();
            break;
        } else if (reverse || new_index == -1)
            new_index = vec[i]->getIndex();
    }

    if (new_index != -1)
        setActiveIndex(new_index);
}
