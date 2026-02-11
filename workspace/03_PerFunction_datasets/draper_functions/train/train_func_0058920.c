add_steady_state_model_equal(string *varname, expr_t expr)
{
  int id;
  try
    {
      id = mod_file->symbol_table.getID(*varname);
    }
  catch (SymbolTable::UnknownSymbolNameException &e)
    {

      id = mod_file->symbol_table.addSymbol(*varname, eModFileLocalVariable);
    }

  SymbolType type = mod_file->symbol_table.getType(id);
  if (type != eEndogenous && type != eModFileLocalVariable && type != eParameter)
    error(*varname + " has incorrect type");

  mod_file->steady_state_model.addDefinition(id, expr);

  delete varname;
}
