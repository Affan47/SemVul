luaQ_doevents(lua_State *L)
{
  QtLuaEngine::Private *d = luaQ_private(L);

  QMutexLocker locker(&d->mutex);
  bool saved_rflag = d->rflag;
  bool more = true;
  while (more)
    {
      locker.unlock();
      QCoreApplication::processEvents(QEventLoop::AllEvents, 0);
      locker.relock();
      more = d->processQueuedSignals(locker);
    }
  bool new_rflag = d->rflag;
  d->rflag = saved_rflag;
  locker.unlock();
  if (new_rflag && !saved_rflag)
    emit d->emitStateChanged(QtLuaEngine::Ready);
  if (saved_rflag && !new_rflag)
    emit d->emitStateChanged(QtLuaEngine::Running);
}
