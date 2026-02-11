alloc_texgen_data( struct gl_context *ctx,
				    struct tnl_pipeline_stage *stage )
{
   struct vertex_buffer *VB = &TNL_CONTEXT(ctx)->vb;
   struct texgen_stage_data *store;
   GLuint i;

   stage->privatePtr = calloc(1, sizeof(*store));
   store = TEXGEN_STAGE_DATA(stage);
   if (!store)
      return GL_FALSE;

   for (i = 0 ; i < ctx->Const.MaxTextureCoordUnits ; i++)
      _mesa_vector4f_alloc( &store->texcoord[i], 0, VB->Size, 32 );

   store->tmp_f = malloc(VB->Size * sizeof(GLfloat) * 3);
   store->tmp_m = malloc(VB->Size * sizeof(GLfloat));

   return GL_TRUE;
}
