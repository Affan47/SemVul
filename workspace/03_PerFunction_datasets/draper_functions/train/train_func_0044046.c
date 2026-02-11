run_timer(Timer *)
{
  if (_debug) {
    click_chatter("%s %{element}::%s\n",
		  Timestamp::now().unparse().c_str(), this, __func__);

  }

  if (_q || _signal) {
    if (add_select(_fd, SELECT_WRITE) < 0) {
      click_chatter("%s %{element}::%s add_select failed %d\n",
		    Timestamp::now().unparse().c_str(), this, __func__, _fd);
    }
    selected(_fd);
  }
}
