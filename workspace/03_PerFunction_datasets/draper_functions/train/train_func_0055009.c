all_tty_idle(time_t t) {
    static vector<string> tty_list;
    struct stat sbuf;
    unsigned int i;

    if (tty_list.size()==0) tty_list=get_tty_list();
    for (i=0; i<tty_list.size(); i++) {

        if (!stat(tty_list[i].c_str(), &sbuf)) {

            if (sbuf.st_atime >= t) {
                return false;
            }
        }
    }
    return true;
}
