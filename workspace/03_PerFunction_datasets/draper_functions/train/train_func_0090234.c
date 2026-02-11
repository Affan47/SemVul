gtk_search() {
  bool found;
  Gtk::TextIter iter, start, end;
  while (true) {
    if (_search_from_beginning)
      {
	if (_search_backwards) {
	  iter = _text_view.get_buffer()->end();
	}
	else {
	  iter = _text_view.get_buffer()->begin();
	}
      }
    else {
      Gtk::TextIter dummy1, dummy2;
      if (_text_view.get_buffer()->get_selection_bounds(dummy1, dummy2)) {
	if (_search_backwards) {
	  iter = dummy1;
	}
	else {
	  iter = dummy2;
	}
      }
      else {
	iter = _text_view.get_buffer()->get_iter_at_mark(_text_view.get_buffer()->get_insert());
      }
    }

    if (_search_backwards) {
      found = iter.backward_search(_search_text, Gtk::TextSearchFlags(Gtk::TEXT_SEARCH_TEXT_ONLY|Gtk::TEXT_SEARCH_VISIBLE_ONLY), start, end);
    }
    else {
      found = iter.forward_search(_search_text, Gtk::TextSearchFlags(Gtk::TEXT_SEARCH_TEXT_ONLY|Gtk::TEXT_SEARCH_VISIBLE_ONLY), start, end);
    }

    if ((found) && ((_search_whole_word) && (is_whole_word(start, end)))) {
      highlight(start, end);
      _search_from_beginning = false;
      return true;
    }
    else if ((found) && (!_search_whole_word)) {
      highlight(start, end);
      _search_from_beginning = false;
      return true;
    }
    else if ((_search_wrap) && (!_search_from_beginning)) {
      _search_from_beginning = true;
      return gtk_search();
    }
    else {
      return false;
    }
  }
}
