sighandler(int sig) {
    Q_UNUSED(sig);

    dynamic_cast<Application*> (qApp)->close();
}
