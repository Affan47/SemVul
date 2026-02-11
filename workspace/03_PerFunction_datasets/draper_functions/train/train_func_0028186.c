unprotect(const QString string)
{
    QString string2 = QString::fromLocal8Bit(string.toAscii().data());


    QString s = string2.mid(1,string2.length()-2);


    s.replace("\\t", "\t");
    s.replace("\\n", "\n");
    s.replace("\\r", "\r");
    s.replace("\\b", "\b");
    s.replace("\\f", "\f");
    s.replace("\\/", "/");
    s.replace("\\\"", "\"");
    s.replace("\\\\", "\\");

    return s;
}
