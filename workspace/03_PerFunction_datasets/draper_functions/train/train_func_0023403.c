dump_processor_list(void)
{

  cout << "Processor List\n";

  bool have_processors = 0;
  CProcessorList::iterator processor_iterator;
  for (processor_iterator = processor_list.begin();
       processor_iterator != processor_list.end();
       processor_iterator++) {
      CProcessorList::value_type vt = *processor_iterator;
      Processor *p = vt.second;
      cout << p->name() << '\n';
      have_processors = 1;
    }

  if(!have_processors)
    cout << "(empty)\n";

}
