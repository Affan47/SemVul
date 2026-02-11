saveState (QDataStream & stream) {
    KJavaApplet* const applet = static_cast<KJavaAppletViewer*>(parent())->view()->appletWidget ()->applet ();
    stream << applet->appletClass();
    stream << applet->baseURL();
    stream << applet->archives();
    stream << applet->getParams().size ();
    QMap<QString,QString>::const_iterator it = applet->getParams().constBegin();
    const QMap<QString,QString>::const_iterator itEnd = applet->getParams().constEnd();
    for ( ; it != itEnd; ++it) {
        stream << it.key ();
        stream << it.value ();
    }
}
