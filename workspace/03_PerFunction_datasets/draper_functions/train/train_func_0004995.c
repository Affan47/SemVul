build_receiver_ref (tree var, bool by_ref, omp_context *ctx)
{
  tree x, field = lookup_field (var, ctx);


  x = maybe_lookup_field (field, ctx);
  if (x != NULL)
    field = x;

  x = build_simple_mem_ref (ctx->receiver_decl);
  x = omp_build_component_ref (x, field);
  if (by_ref)
    x = build_simple_mem_ref (x);

  return x;
}
