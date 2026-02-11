object_expr(const string& expr) const
{
  if (find(preset_keywords_rep.begin(), preset_keywords_rep.end(), expr) != preset_keywords_rep.end()) {
    return(object(expr));
  }
  return(0);
}
