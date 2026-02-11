readLineChecked(QIODevice *dev, QByteArray *line)
{
    *line = dev->readLine(MAX_IPC_SIZE);

    if (line->isEmpty() || !line->endsWith('\n')) {
        return false;
    }

    line->chop(1);
    return true;
}
