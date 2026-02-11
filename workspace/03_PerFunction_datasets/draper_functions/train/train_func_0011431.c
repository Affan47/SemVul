waitForReturnData(JSStackFrame * frame) {
    kDebug(6100) << ">KJavaAppletServer::waitForReturnData";
    killTimers();
    startTimer(15000);
    while (!frame->exit) {
        QAbstractEventDispatcher::instance()->processEvents (QEventLoop::AllEvents | QEventLoop::WaitForMoreEvents);
    }
    if (d->jsstack.size() <= 1)
        killTimers();
    kDebug(6100) << "<KJavaAppletServer::waitForReturnData stacksize:" << d->jsstack.size();
}
