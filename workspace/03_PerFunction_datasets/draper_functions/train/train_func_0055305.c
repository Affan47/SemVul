event_abbreviation(char symbol, char *string, char container)

{
  if (container == '!') {
    emit_string("U:");
    emit_char(symbol);
    emit_string_sprintf(" = !%s!", string);
  } else {
    emit_string("U:");
    emit_char(symbol);
    emit_string_sprintf(" = %s", string);
  };
  inmusic = 0;
}
