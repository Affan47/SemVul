module(cmd_options_str *cos)
{

  if(!cos)
    return;

  switch(cos->co->value)
    {
    case CMD_MOD_LIB:
      if(verbose)
        cout << "module command got the library " << cos->str << endl;

      try {
        string fname(cos->str);
        ModuleLibrary::LoadFile(fname);
      }
      catch(Error *pError) {
        cout << pError->get_errMsg();
      }

      break;
    case CMD_MOD_LOAD:


      if(verbose)
        cout << "module command got the module " << cos->str << '\n';
#ifdef OLD_MODULE_LIBRARY
      if(ModuleLibrary::NewObject(cos->str) == NULL) {
        GetUserInterface().DisplayMessage("module type %s not created\n", cos->str);
      }
#else
      {
        cout << "Fixme -- module NewObject\n";
      }
#endif

      break;

    case CMD_MOD_DUMP:
      cout <<  " is not supported yet\n";
      break;

    case CMD_MOD_PINS:
      cout << "Fixme: display module pins is not supported...\n";

      break;

    default:
      cout << "cmd_module error\n";
    }

}
