delete_context(context* old_context) {
  unused_contexts.push_back(old_context);
  active_contexts.erase(old_context);

  while (unused_contexts.size() > 10) {
    context* stale_context = unused_contexts.front();
    unused_contexts.pop_front();
    delete stale_context;
  }
}
