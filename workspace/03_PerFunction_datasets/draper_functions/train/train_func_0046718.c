clutter_input_device_sequence_ungrab (ClutterInputDevice   *device,
                                      ClutterEventSequence *sequence)
{
  ClutterActor *grab_actor;

  g_return_if_fail (CLUTTER_IS_INPUT_DEVICE (device));

  if (device->sequence_grab_actors == NULL)
    return;

  grab_actor = g_hash_table_lookup (device->sequence_grab_actors, sequence);

  if (grab_actor == NULL)
    return;

  g_signal_handlers_disconnect_by_func (grab_actor,
                                        G_CALLBACK (on_grab_sequence_actor_destroy),
                                        device);
  g_hash_table_remove (device->sequence_grab_actors, sequence);
  g_hash_table_remove (device->inv_sequence_grab_actors, grab_actor);

  if (g_hash_table_size (device->sequence_grab_actors) == 0)
    {
      g_hash_table_destroy (device->sequence_grab_actors);
      device->sequence_grab_actors = NULL;
      g_hash_table_destroy (device->inv_sequence_grab_actors);
      device->inv_sequence_grab_actors = NULL;
    }
}
