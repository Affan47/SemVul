ecore_animator_source_set(Ecore_Animator_Source source)
{
   EINA_MAIN_LOOP_CHECK_RETURN;
   _ecore_lock();
   src = source;
   _end_tick();
   if (animators) _begin_tick();
   _ecore_unlock();
}
