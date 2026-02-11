write(QDataStream& s)
{
    for (int i = 0; i < size(); i++)
        s << at(i);
}
