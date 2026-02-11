restart(QTime &t) const
    {
        QTime time = QTime::currentTime();
        int n = t.msecsTo(time);
        if (n < 0)
            n += 86400*1000;
        t = time;
        return n;
    }
