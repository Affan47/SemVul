LogRegExpSource(Handle<JSRegExp> regexp) {


  LogMessageBuilder msg;

  Handle<Object> source = GetProperty(regexp, "source");
  if (!source->IsString()) {
    msg.Append("no source");
    return;
  }

  switch (regexp->TypeTag()) {
    case JSRegExp::ATOM:
      msg.Append('a');
      break;
    default:
      break;
  }
  msg.Append('/');
  msg.AppendDetailed(*Handle<String>::cast(source), false);
  msg.Append('/');


  Handle<Object> global = GetProperty(regexp, "global");
  if (global->IsTrue()) {
    msg.Append('g');
  }

  Handle<Object> ignorecase = GetProperty(regexp, "ignoreCase");
  if (ignorecase->IsTrue()) {
    msg.Append('i');
  }

  Handle<Object> multiline = GetProperty(regexp, "multiline");
  if (multiline->IsTrue()) {
    msg.Append('m');
  }

  msg.WriteToLogFile();
}
