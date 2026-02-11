CheckAndDropActivations(
    Handle<JSArray> shared_info_array, bool do_drop) {
  int len = Smi::cast(shared_info_array->length())->value();

  Handle<JSArray> result = Factory::NewJSArray(len);


  for (int i = 0; i < len; i++) {
    SetElement(result, i,
               Handle<Smi>(Smi::FromInt(FUNCTION_AVAILABLE_FOR_PATCH)));
  }


  InactiveThreadActivationsChecker inactive_threads_checker(shared_info_array,
                                                            result);
  ThreadManager::IterateArchivedThreads(&inactive_threads_checker);
  if (inactive_threads_checker.HasBlockedFunctions()) {
    return result;
  }


  const char* error_message =
      DropActivationsInActiveThread(shared_info_array, result, do_drop);
  if (error_message != NULL) {

    Vector<const char> vector_message(error_message, StrLength(error_message));
    Handle<String> str = Factory::NewStringFromAscii(vector_message);
    SetElement(result, len, str);
  }
  return result;
}
