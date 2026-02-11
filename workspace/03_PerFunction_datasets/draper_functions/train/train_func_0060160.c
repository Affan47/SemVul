shutdown()
{
    QDBusReply<void> reply;
    if (d->login1Interface->isValid())
        reply = d->login1Interface->call("PowerOff", false);
    else
        reply = d->consoleKitInterface->call("Stop");
    return reply.isValid();
}
