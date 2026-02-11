notify (ACE_Event_Handler *event_handler,
                     ACE_Reactor_Mask mask,
                     ACE_Time_Value *tv)
{


  if (event_handler != 0 && event_handler->reactor () == 0)
    {
      event_handler->reactor (this);
    }
  return this->implementation ()->notify (event_handler, mask, tv);
}
