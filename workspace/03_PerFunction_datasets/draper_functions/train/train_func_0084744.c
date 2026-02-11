ralloc_size(const void *ctx, size_t size)
{
   void *block = calloc(1, size + sizeof(ralloc_header));

   ralloc_header *info = (ralloc_header *) block;
   ralloc_header *parent = ctx != NULL ? get_header(ctx) : NULL;

   add_child(parent, info);

   info->canary = CANARY;

   return PTR_FROM_HEADER(info);
}
