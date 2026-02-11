handleMarkFuncDirective(Node *n) {
    String *markfunc = Getattr(n, "feature:markfunc");
    if (markfunc) {
      Printf(klass->init, "SwigClass%s.mark = (void (*)(void *)) %s;\n", klass->name, markfunc);
    } else {
      Printf(klass->init, "SwigClass%s.mark = 0;\n", klass->name);
    }
  }
