output(const conststring type, const conststring rel,
		   conststring url)
{
  string h = NULL, rel1;

  if (url) {
    if (! relative && base) {
      h = URL_s_absolutize(base, url);
      url = h;
    }
    rel1 = newstring(rel ? rel : "");
    down(rel1);
    switch (format) {
      case HTML:
	printf("<li><a class=\"%s\" rel=\"%s\" href=\"%s\">%s</a></li>\n",
		 type, rel1, url, url);
	break;
      case Long:
	printf("%s\t%s\t%s\n", type, rel1, url);
	break;
      case Short:
	printf("%s\n", url);
	break;
      case Tuple:
	printf("%s\t%s\t%s\t%s\n", self, type, rel1, url);
	break;
      default:
	assert(!"Cannot happen!");
    }
    free(rel1);
    free(h);
  }
}
