availableStatus() {
    return QStringList()
            << tkTr(Trans::Constants::WAITING)
            << tkTr(Trans::Constants::APPROVED)
            << tkTr(Trans::Constants::ARRIVED)
            << tkTr(Trans::Constants::CHANGED)
            << tkTr(Trans::Constants::CANCELLED)
            << tkTr(Trans::Constants::MISSED)
               ;
}
