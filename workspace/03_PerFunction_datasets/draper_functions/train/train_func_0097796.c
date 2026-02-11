need_to_reassign_continents(const struct terrain *oldter,
                                 const struct terrain *newter)
{
  bool old_is_ocean, new_is_ocean;

  if (!oldter || !newter) {
    return FALSE;
  }

  old_is_ocean = is_ocean(oldter);
  new_is_ocean = is_ocean(newter);

  return (old_is_ocean && !new_is_ocean)
    || (!old_is_ocean && new_is_ocean);
}
