flush()
{
  int min_useful_message = _messages.size();
  if (min_useful_message)
    for (int i = 0; i < _fd_alive.size(); i++)
      if (_fd_alive[i] >= 0) {
	int m = flush(i);
	if (m < min_useful_message)
	  min_useful_message = m;
      }


  if (min_useful_message >= 10) {
    _messages.erase(_messages.begin(), _messages.begin() + min_useful_message);
    _message_pos.erase(_message_pos.begin(), _message_pos.begin() + min_useful_message);
  }
}
