remove(Pixmap p) {
    ImageHolder* doomed;
    if (_table.find(doomed, p)) {
        _table.remove(p);
        delete doomed;
    }
}
