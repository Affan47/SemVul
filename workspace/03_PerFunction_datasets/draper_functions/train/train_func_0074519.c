Xml_print_node(Node *obj) {
    Node *cobj;

    print_indent(0);
    Printf(out, "<%s id=\"%ld\" addr=\"%x\" >\n", nodeType(obj), ++id, obj);
    Xml_print_attributes(obj);
    cobj = firstChild(obj);
    if (cobj) {
      indent_level += 4;
      Printf(out, "\n");
      Xml_print_tree(cobj);
      indent_level -= 4;
    } else {
      print_indent(1);
      Printf(out, "\n");
    }
    print_indent(0);
    Printf(out, "</%s >\n", nodeType(obj));
  }
