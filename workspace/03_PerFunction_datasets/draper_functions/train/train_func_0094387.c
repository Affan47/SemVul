doFinalization(Module &M) {


  Module::GlobalListType &global_list = M.getGlobalList();
  int i, n = global_list.size();
  GlobalVariable **gv_array = new GlobalVariable* [n];


  i = 0;
  for (Module::global_iterator I = global_list.begin(), E = global_list.end();
       I != E; ++I)
    gv_array[i++] = &*I;


  while (!global_list.empty())
    global_list.remove(global_list.begin());


  bool ret = AsmPrinter::doFinalization(M);


  for (i = 0; i < n; i ++)
    global_list.insert(global_list.end(), gv_array[i]);

  delete[] gv_array;
  return ret;
}
