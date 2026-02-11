SP_target_goal (edict_t * ent)
{
  if (deathmatch->value)
    {
      G_FreeEdict (ent);
      return;
    }

  ent->use = use_target_goal;
  if (!st.noise)
    st.noise = "misc/secret.wav";
  ent->noise_index = gi.soundindex (st.noise);
  ent->svflags = SVF_NOCLIENT;
  level.total_goals++;
}
