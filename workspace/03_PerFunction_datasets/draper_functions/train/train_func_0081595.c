_mesa_lookup_parameter_value(const struct gl_program_parameter_list *paramList,
                             GLsizei nameLen, const char *name)
{
   GLint i = _mesa_lookup_parameter_index(paramList, nameLen, name);
   if (i < 0)
      return NULL;
   else
      return paramList->ParameterValues[i];
}
