find_runnable_in_list(Task_list* tasks)
{
  Task* t;
  while ((t = tasks->pop_front()) != NULL)
    {
      Task_token* token = t->is_runnable();

      if (token == NULL)
	return t;

      token->add_waiting(t);
      ++this->waiting_;
    }


  return NULL;
}
