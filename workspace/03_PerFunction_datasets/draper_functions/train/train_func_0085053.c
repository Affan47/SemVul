invokeCallbackList(std::list<ArFunctor*> *cbList)
{
  if (cbList == NULL) {
    ArLog::log(ArLog::Terse,
               "ArMapSimple::invokeCallbackList failed because list is null");
    return;
  }
  for (std::list<ArFunctor*>::iterator iter = cbList->begin();
       iter != cbList->end();
       iter++) {
    ArFunctor *cb = *iter;
    if (cb == NULL) {
      continue;
    }
    cb->invoke();
  }
}
