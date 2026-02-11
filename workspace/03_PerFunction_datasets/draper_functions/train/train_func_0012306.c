setShow(bool show) {
    this->show = show;

    for(std::vector<FileKeyEntry*>::iterator it = active_keys.begin(); it != active_keys.end(); it++) {

        FileKeyEntry* entry = *it;

        entry->setShow(show);
    }
    interval_remaining = 0.0f;
}
