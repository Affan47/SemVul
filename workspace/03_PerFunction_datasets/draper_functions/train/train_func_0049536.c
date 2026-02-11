remove_array_object( struct gl_context *ctx, struct gl_array_object *obj )
{
   if (obj->Name > 0) {

      _mesa_HashRemove(ctx->Array.Objects, obj->Name);
   }
}
