vcf_print_utf(const utf_string *s)
{
  char *p, *p2, *p3;
  char *stripped_html;

  if (!s) {
    return;
  }

  stripped_html = strip_html(s);
  p = gstrsub(stripped_html, "\n", "\\n");
  p2 = gstrsub(p, "<p>", "\\n");
  p3 = gstrsub(p2, ";", "\\;");
  gbfputs(p3, file_out);
  xfree(p);
  xfree(p2);
  xfree(p3);
  xfree(stripped_html);
}
