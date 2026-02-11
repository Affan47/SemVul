event_handle_gchord(s)
char* s;


{
  if (cv->gchords_pending == NULL) {
    cv->gchords_pending = newlist();
  };
  if (*s == '_') {
  if (cv->instructions_pending == NULL) {
    cv->instructions_pending = newlist();
    };
  addtolist(cv->instructions_pending, addstring(s+1));
  } else {
    addtolist(cv->gchords_pending, addstring(s));
  };
}
