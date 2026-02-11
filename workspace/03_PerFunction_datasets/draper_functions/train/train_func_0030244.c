revert(std::string& err) {
  std::string contents;
  if (!Utils::katoob_read(_file, contents)) {
    err = contents;
    return false;
  }

  if (_encoding == _encodings.utf8()) {
    _text_view.get_buffer()->set_text(contents);
  }
  else {
    std::string c;
    if (!_encodings.convert_to(contents, c, _encoding) == -1) {
      err = c;
      return false;
    }
    else {
      _text_view.get_buffer()->set_text(c);
    }
  }

  clear_do(_undo);
  clear_do(_redo);
  set_modified(false);
  signal_can_undo.emit(false);
  signal_can_redo.emit(false);
  return true;
}
