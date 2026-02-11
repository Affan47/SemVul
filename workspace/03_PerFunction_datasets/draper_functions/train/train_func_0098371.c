getCallCount(TraceFunction *f) const
{
    QString str;
    if (f->calledCount() > 0)
      str = f->prettyCalledCount();
    else {
      if (f == f->cycle())
        str = QString("-");
      else
        str = QString("(0)");
    }
    return str;
}
