destroyContext(gem::Context*ctx){
  if(ctx)delete ctx;
  ctx=NULL;
  return ctx;
}
