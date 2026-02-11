expt2str (ExecState *exec)
{
    JSValue *expt = exec->exception();
    if (   expt->isObject()
        && expt->getObject()->hasProperty(exec, "message"))
    {
        JSValue *msg = expt->getObject()->get(exec, "message");
        return QString::fromLatin1("Error: %1").arg(msg->getString().qstring());
    }
    else
    {
        QString strexpt = exec->exception()->toString(exec).qstring();
        return QString::fromLatin1("Caught exception: %1").arg(strexpt);
    }
}
