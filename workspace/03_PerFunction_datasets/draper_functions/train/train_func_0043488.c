container_add_valist (ClutterContainer *container,
                      ClutterActor     *first_actor,
                      va_list           args)
{
  ClutterActor *actor = first_actor;

  while (actor != NULL)
    {
      container_add_actor (container, actor);
      actor = va_arg (args, ClutterActor *);
    }
}
