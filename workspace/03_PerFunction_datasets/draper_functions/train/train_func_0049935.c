define(const char *URI, const char *name, const xs__complexType& complexType)
{
  const char *prefix = NULL;
  if (complexType.name)
    name = complexType.name;
  else
    prefix = "_";
  if (complexType.complexContent
   && complexType.complexContent->restriction
   && !strcmp(complexType.complexContent->restriction->base, "SOAP-ENC:Array"))
  { if (strcmp(schema_prefix, "ns"))
      prefix = "*";
    else
      prefix = "";
  }
  if (cflag)
  { const char *t = deftname(STRUCT, "*", true, prefix, URI, name);
    if (t)
    { if (yflag)
        fprintf(stream, "\n/// Typedef synonym for struct %s.\ntypedef struct %s %s;\n", t, t, t);
    }
    else if (name)
    { t = deftypemap[cname(prefix, URI, name)];
      if (t)
      { fprintf(stream, "\n/// Imported complexType \"%s\":%s from typemap %s.\n", URI, name, mapfile?mapfile:"");
        document(complexType.annotation);
        if (*t)
          format(t);
        else
          fprintf(stream, "// complexType definition intentionally left blank.\n");
      }
    }
  }
  else
  { const char *t = deftname(CLASS, "*", true, prefix, URI, name);
    if (t)
      fprintf(stream, "\n//  Forward declaration of class %s.\nclass %s;\n", t, t);
    else if (name)
    { t = deftypemap[cname(prefix, URI, name)];
      if (t)
      { fprintf(stream, "\n/// Imported complexType \"%s\":%s from typemap %s.\n", URI, name, mapfile?mapfile:"");
        document(complexType.annotation);
        if (*t)
          format(t);
        else
          fprintf(stream, "// complexType definition intentionally left blank.\n");
      }
    }
  }
}
