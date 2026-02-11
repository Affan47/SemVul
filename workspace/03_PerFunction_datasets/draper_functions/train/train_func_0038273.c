dfs(const Expr& e1, const Expr& e2)
{
  if(e1 == e2)
    return true;
  if(d_cache.count(e2) > 0)
    return false;
  if(d_edges.count(e2) == 0)
    return false;
  d_cache[e2] = true;
  vector<Expr>& e2Edges = d_edges[e2];
  vector<Expr>::iterator i = e2Edges.begin();
  vector<Expr>::iterator iend = e2Edges.end();

  for(; i != iend && !dfs(e1,*i); ++i);
  return (i != iend);
}
