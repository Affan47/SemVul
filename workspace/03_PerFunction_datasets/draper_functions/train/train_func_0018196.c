Q_Insert(queue *q, void *data, int (*Comp)(const void *, const void *))
{
      Q_PushHead(q, data);

      if (!Q_Sort(q, Comp))
            return False_;

      return True_;
}
