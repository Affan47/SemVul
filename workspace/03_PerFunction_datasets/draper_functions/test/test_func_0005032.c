action()
{
  TriggerAction::action();
  if(to && verbosity && verbosity->getVal())
    to->print();
}
