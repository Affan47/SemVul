IsExcluded(cmLocalGenerator* root,
                                   cmLocalGenerator* gen)
{
  if(!gen || gen == root)
    {

    return false;
    }

  if(gen->GetMakefile()->GetPropertyAsBool("EXCLUDE_FROM_ALL"))
    {

    return true;
    }


  return this->IsExcluded(root, gen->GetParent());
}
