propagate()
{
  while(!_queue.empty())
  {
    ConstraintObj* __c = _queue.back();
    _queue.pop_back();
    __c->set_in_queue(false);
    __c->propagate();
  }

}
