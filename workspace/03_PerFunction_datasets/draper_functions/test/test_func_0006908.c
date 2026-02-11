generate_decl()
{
  if (!declared)
    {
      if ( name == NULL )
    {
      name = tsprintf("_scalarset_%d", tNum );
      mu_name = tsprintf("mu_%s",name);
    }


      fprintf(codefile,
          "class %s: public %s\n"
          "{\n"
          " public:\n"
          "  inline int operator=(int val) { return value(val); };\n"
          "  inline int operator=(const %s& val){"
          " return value(val.value());};\n"
          "  inline operator int() const { return value(); };\n"
          "  static char *values[];\n"
          "  friend ostream& operator<< (ostream& s, %s& val)\n"
          "    {\n"
          "      if (val.defined())\n"
          "        return ( s << %s::values[ int(val) - %d ] );\n"
          "      else\n"
          "        return ( s << \"Undefined\" );\n"
          "    };\n\n"
          "  %s (char *name, int os): %s(%d, %d, %d, name, os) {};\n"
          "  %s (void): %s(%d, %d, %d) {};\n"
          "  %s (int val): %s(%d, %d, %d, \"Parameter or function result.\", 0)\n"
          "    { operator=(val); };\n",
          mu_name, mu_type,
          mu_name,
          mu_name,
          mu_name,
          left,
          mu_name, mu_type, left, right, numbits,

          mu_name, mu_type, left, right, numbits,

          mu_name, mu_type, left, right, numbits);


       fprintf(codefile,
           "  char * Name() { return values[ value() -%d]; };\n"


           "  virtual void print()\n"
           "    {\n"
           "      if (defined()) cout << name << ':' << values[ value() - %d] << '\\n';\n"
           "      else cout << name << \":Undefined\\n\";\n"
           "    };\n",
           left,
           left);

        fprintf(codefile,
           "  void print_statistic() {};\n"
           );


       fprintf(codefile,
           "friend int CompareWeight(%s& a, %s& b)\n"
           "{\n"
           "  if (!a.defined() && b.defined())\n"
           "    return -1;\n"
           "  else if (a.defined() && !b.defined())\n"
           "    return 1;\n"
           "  else\n"
           "    return 0;\n"
           "}\n",
           mu_name, mu_name
           );


       theprog->symmetry.generate_symmetry_function_decl();


       fprintf(codefile,"};\n");


       fprintf(codefile,
          "char *%s::values[] =\n"
          "  { ",
          mu_name);
       make_scalarset_idvalues(idvalues, getsize(), named);
       fprintf(codefile,"NULL };\n\n");
       fprintf(codefile, "/*** end scalarset declaration ***/\n");
       fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);

       declared = TRUE;
     }
   return "ERROR!";
 }
