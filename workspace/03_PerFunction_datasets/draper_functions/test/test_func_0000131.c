savereslimit(const char *name,rlim_t soft,rlim_t hard)
{
  struct resource *res;
  struct reslimit *lim;
  res=getresourcebyname(name);
  if (res==NULL)
  {
    log_log(LOG_ERR,"cannot find resource %s",name);
    exit(1);
  }
  lim=(struct reslimit *)xmalloc(sizeof(struct reslimit));
  lim->resource=res;
  lim->limit.rlim_cur=soft;
  lim->limit.rlim_max=hard;
  lim->next=savedlimits;
  savedlimits=lim;
}
