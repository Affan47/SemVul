Xml_print_hash(Hash *p, const char *markup) {

    print_indent(0);
    Printf(out, "<%s id=\"%ld\" addr=\"%x\" >\n", markup, ++id, p);
    Xml_print_attributes(p);
    indent_level += 4;
    Iterator n = First(p);
    while (n.key) {
      print_indent(0);
      Printf(out, "<%ssitem id=\"%ld\" addr=\"%x\" >\n", markup, ++id, n.item);
      Xml_print_attributes(n.item);
      print_indent(0);
      Printf(out, "</%ssitem >\n", markup);
      n = Next(n);
    }
    indent_level -= 4;
    print_indent(0);
    Printf(out, "</%s >\n", markup);
  }
