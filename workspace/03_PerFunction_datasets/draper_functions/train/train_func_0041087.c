doMode(QAction *action)
{
  if (action)
    {
      void *data = qVariantValue<void*>(action->data());
      QLuaTextEditModeFactory *f = (data) ? (QLuaTextEditModeFactory*)data : 0;
      q->doMode(f);
    }
}
