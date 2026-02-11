get_stack (NODE_T * p, FILE_T out, char * dst, char * cast)
{
  if (DEBUG_LEVEL >= 4) {
    if (LEVEL (GINFO (p)) == global_level) {
      indentf (out, snprintf (line, SNPRINTF_SIZE, "GET_GLOBAL (%s, %s, %d);\n", dst, cast, OFFSET (TAX (p))));
    } else {
      indentf (out, snprintf (line, SNPRINTF_SIZE, "GET_FRAME (%s, %s, %d, %d);\n", dst, cast, LEVEL (GINFO (p)), OFFSET (TAX (p))));
    }
  } else {
    indentf (out, snprintf (line, SNPRINTF_SIZE, "GET_FRAME (%s, %s, %d, %d);\n", dst, cast, LEVEL (GINFO (p)), OFFSET (TAX (p))));
  }
}
