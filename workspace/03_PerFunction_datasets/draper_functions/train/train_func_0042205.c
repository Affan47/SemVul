checkPass(ModFileStructure &mod_file_struct, WarningConsolidation &warnings)
{
  set<int> exogs = getUninitializedVariables(eExogenous);
  set<int> endogs = getUninitializedVariables(eEndogenous);

  if (endogs.size() > 0)
    {
      cerr << "ERROR: You have not set the following endogenous variables in initval:";
      for (set<int>::const_iterator it = endogs.begin(); it != endogs.end(); it++)
        cerr << " " << symbol_table.getName(*it);
      cerr << endl;
    }

  if (exogs.size() > 0)
    {
      cerr << "ERROR: You have not set the following exogenous variables in initval:";
      for (set<int>::const_iterator it = exogs.begin(); it != exogs.end(); it++)
        cerr << " " << symbol_table.getName(*it);
      cerr << endl;
    }

  if (endogs.size() > 0 || exogs.size() > 0)
    exit(EXIT_FAILURE);
}
