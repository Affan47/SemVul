raptor_serializer_serialize_statement(raptor_serializer* serializer,
                                      raptor_statement* s)
{
  FILE *fh = serializer->fh;

  if(s->subject->type == RAPTOR_TERM_TYPE_URI)
    fprintf(fh, "<%s>", (const char*)s->subject->value.uri);
  else
    fprintf(fh, "_:%s", (const char*)s->subject->value.blank.string);

  fprintf(fh, " <%s> ", (const char*)s->predicate->value.uri);

  if(s->object->type == RAPTOR_TERM_TYPE_LITERAL) {
    const char *p;
    char c;

    fputc('"', fh);
    for(p = (const char*)s->object->value.literal.string; (c = *p); p++) {
      if(c == '\n') {
        fputs("\\\n", fh);
        continue;
      } else if(c == '\t') {
        fputs("\\\t", fh);
        continue;
      } if(c == '\r') {
        fputs("\\\r", fh);
        continue;
      } else if(c == '"' || c == '\\')
        fputc('\\', fh);
      fputc(c, fh);
    }
    fputc('"', fh);
    if(s->object->value.literal.datatype)  {
      fputs("^^<", fh);
      fputs((const char*)s->object->value.literal.datatype, fh);
      fputc('>', fh);
    }
  } else if(s->object->type == RAPTOR_TERM_TYPE_URI)
    fprintf(fh, "<%s>", (const char*)s->object->value.uri);
  else
    fprintf(fh, "_:%s", (const char*)s->object->value.blank.string);

  fputs(" . \n", fh);
}
