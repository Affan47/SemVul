checkPRChain (const DatabaseInfo database, ErrorDesc *err)
{
  IndexDesc desc = getIndexDesc (database);
  PR *new_chain = getNewIndexIfChanged (database, err);

  if (new_chain != NULL)
    {
      freePRChain (desc->prChain);
      desc->prChain = new_chain;
      return 1;
    }
  else
    {
      return 0;
    }
}
