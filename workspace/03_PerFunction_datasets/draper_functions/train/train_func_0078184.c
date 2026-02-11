operator()(cmTarget* l, cmTarget* r) const
{

  if(int c = strcmp(l->GetName(), r->GetName()))
    {
    return c < 0;
    }

  return strcmp(l->GetMakefile()->GetCurrentOutputDirectory(),
                r->GetMakefile()->GetCurrentOutputDirectory()) < 0;
}
