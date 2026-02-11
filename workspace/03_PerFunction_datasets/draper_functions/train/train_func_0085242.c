name() const {
    beforeRead();
    static const std::string blank;
    if (m_data != NULL) {
        return m_data->name;
    } else {
        return blank;
    }
}
