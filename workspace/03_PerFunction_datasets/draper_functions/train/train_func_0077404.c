modelReset()
{
    qDebug() << "@@@@@@@@@@@" << "modelReset";
    if (pedantic) {
        Q_ASSERT(status.type == Status::Resetting);
        refreshStatus();
    }
}
