IsExternallyCaught() {
  ASSERT(has_pending_exception());

  if ((thread_local_top()->catcher_ == NULL) ||
      (try_catch_handler() != thread_local_top()->catcher_)) {


    return false;
  }

  if (!is_catchable_by_javascript(pending_exception())) {
    return true;
  }


  Address external_handler_address =
      thread_local_top()->try_catch_handler_address();
  ASSERT(external_handler_address != NULL);


  StackHandler* handler =
      StackHandler::FromAddress(Isolate::handler(thread_local_top()));
  while (handler != NULL && handler->address() < external_handler_address) {
    ASSERT(!handler->is_try_catch());
    if (handler->is_try_finally()) return false;

    handler = handler->next();
  }

  return true;
}
