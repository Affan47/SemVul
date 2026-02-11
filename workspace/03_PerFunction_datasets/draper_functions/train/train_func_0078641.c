normalized() const
{
    if(s > e)
        return QMediaTimeInterval(e, s);

    return *this;
}
