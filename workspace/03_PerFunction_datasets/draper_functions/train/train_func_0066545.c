parseIPString(const QString& input, QHostAddress * ip, quint16 * port)
{
    bool result = false;
    ip->setAddress(input.left(input.indexOf(":")));
    *port = input.mid(input.indexOf(":") + 1).toUInt(&result);
    return result;
}
