classify_identifier(struct _mesa_glsl_parse_state *state, const char *name)
{
   if (state->symbols->get_variable(name) || state->symbols->get_function(name))
      return IDENTIFIER;
   else if (state->symbols->get_type(name))
      return TYPE_IDENTIFIER;
   else
      return NEW_IDENTIFIER;
}
