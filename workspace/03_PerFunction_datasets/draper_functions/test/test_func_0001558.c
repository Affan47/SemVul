_eina_value_type_hash_copy_each(const Eina_Hash *hash __UNUSED__, const void *key, void *_ptr, void *user_data)
{
   struct _eina_value_type_hash_copy_each_ctx *ctx = user_data;
   const void *ptr = _ptr;
   void *imem = malloc(ctx->subtype->value_size);
   if (!imem)
     {
        ctx->ret = EINA_FALSE;
        return EINA_FALSE;
     }
   if (!ctx->subtype->copy(ctx->subtype, ptr, imem))
     {
        free(imem);
        ctx->ret = EINA_FALSE;
        return EINA_FALSE;
     }
   if (!eina_hash_add(ctx->dest->hash, key, imem))
     {
        eina_value_type_flush(ctx->subtype, imem);
        free(imem);
        ctx->ret = EINA_FALSE;
        return EINA_FALSE;
     }
   return EINA_TRUE;
}
