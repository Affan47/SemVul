clone_instance()const
{itested();
  DEV_SUBCKT* new_instance = dynamic_cast<DEV_SUBCKT*>(p1.clone());
  new_instance->_parent = this;
  return new_instance;
}
