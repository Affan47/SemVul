agraimentSlot(){
    QDesktopServices::openUrl(QUrl("file:///"+directoriLinux()+
                                charPathSeparator+
                                DIR_HELP+
                                charPathSeparator+
                                "index.html", QUrl::TolerantMode));
}
