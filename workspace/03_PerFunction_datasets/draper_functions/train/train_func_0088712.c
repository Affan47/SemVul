write(CommPortPtr dev, QString &err)
{
    const char *msg = cEscape(data(), payload.count()+2).toAscii().constData();

    if (MACRO_DEBUG) printf("writing '%s' to device\n", msg);

    int n = dev->write(data(), payload.count()+2, err);
    if (n != payload.count()+2) {
        if (n < 0) {
            if (MACRO_DEBUG) printf("failed to write %s to device: %s\n", msg, err.toAscii().constData());
            err = QString(tr("failed to write to device: %1")).arg(err);
        }
        else {
            if (MACRO_DEBUG) printf("timeout writing %s to device\n", msg);
            err = QString(tr("timeout writing to device"));
        }
        return false;
    }

    if (MACRO_DEBUG) printf("writing to device ok\n");
    return true;
}
