prettyName() const
{
    if (_pid==0) return shortName();
    QString name = QString("PID %1").arg(_pid);
    if (_number>0)
        name += QString(", section %2").arg(_number);
    if ((data()->maxThreadID()>1) && (_tid>0))
        name += QString(", thread %3").arg(_tid);
    return name;
}
