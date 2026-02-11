registerAdaptor(const QByteArray &path, AbstractAdaptor *adaptor)
{
    if (path.isEmpty() || d->adaptors.contains(path)) {
        return false;
    }

    d->adaptors[path] = adaptor;
    return true;
}
