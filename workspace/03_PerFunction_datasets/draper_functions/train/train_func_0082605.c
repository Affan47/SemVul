pass_thru_directive (buf, limit, op, keyword)
     U_CHAR *buf, *limit;
     FILE_BUF *op;
     struct directive *keyword;
{
  register int keyword_length = keyword->length;

  check_expand (op, 1 + keyword_length + (limit - buf));
  *op->bufp++ = '#';
  bcopy (keyword->name, (char *) op->bufp, keyword_length);
  op->bufp += keyword_length;
  if (limit != buf && buf[0] != ' ')
    *op->bufp++ = ' ';
  bcopy ((char *) buf, (char *) op->bufp, limit - buf);
  op->bufp += (limit - buf);
#if 0
  *op->bufp++ = '\n';


  op->lineno++;
#endif
}
