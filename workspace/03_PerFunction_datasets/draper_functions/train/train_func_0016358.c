control_app_messages(struct gl_context *ctx, GLenum esource, GLenum etype,
                     GLenum eseverity, GLsizei count, const GLuint *ids,
                     GLboolean enabled)
{
   GLsizei i;
   enum mesa_debug_source source = gl_enum_to_debug_source(esource);
   enum mesa_debug_type type = gl_enum_to_debug_type(etype);
   enum mesa_debug_severity severity = gl_enum_to_debug_severity(eseverity);

   for (i = 0; i < count; i++)
      set_message_state(ctx, source, type, ids[i], enabled);

   if (count)
      return;

   control_messages(ctx, source, type, severity, enabled);
}
