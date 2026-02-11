new_chat ()
{
  SimpleChatPtr chat (new SimpleChat);
  add_simple_chat (chat);
  chat->user_requested ();
}
