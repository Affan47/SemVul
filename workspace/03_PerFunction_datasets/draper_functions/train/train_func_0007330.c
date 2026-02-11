resSize(const QString &str) const
{
    int index = str.indexOf('x');
    if (index != -1) {
        return QSize(str.left(index).toInt(),
                     str.mid(index + 1).toInt());
    } else {
        return QSize();
    }
}
