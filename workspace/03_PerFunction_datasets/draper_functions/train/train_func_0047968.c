handle_message (LmMessage* message)
{
  LmHandlerResult result = LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS;

  if (result == LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS) {

    result = dialect->handle_message (connection, message);
  }

  if (result == LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS) {

    result = cluster->handle_message (connection, message);
  }

#if DEBUG
  if (result == LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS) {

    std::cout << "Nobody cared about : " << lm_message_node_to_string (lm_message_get_node (message)) << std::endl;
  }
#endif

  return result;
}
