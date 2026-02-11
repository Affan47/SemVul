clear() {
    complete = false;
    received = false;
    unsigned int i;
    for (i=0; i<notices.size(); i++) {
        delete notices[i];
    }
    notices.clear();
}
