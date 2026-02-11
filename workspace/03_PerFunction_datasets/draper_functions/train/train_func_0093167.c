maybe_poplevels (int pc)
{
#if defined(DEBUG_JAVA_BINDING_LEVELS)
  current_pc = pc;
#endif


  while (current_binding_level->end_pc <= pc)
    poplevel (1, 0, 0);
}
