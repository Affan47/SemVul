SetPaused(const bool b)
{
    if (b)
    {
        setCursor(Qt::ArrowCursor);
        setToolTip(QString(""));
    }
    else if (mActive)
    {
        setCursor(Qt::PointingHandCursor);
        setToolTip(tr("Commit Your solution"));
    }
    update(boundingRect());
}
