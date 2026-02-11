gap_fmct_add_GapFmacRefEntry(GapLibAinfoType ainfo_type
  , gint32 frame_nr
  , gint32 stackposition
  , gint32 track
  , gint32 drawable_id
  , const char *filename
  , gboolean force_id
  , GapFmacContext *fmacContext)
{
  GapFmacRefEntry *new_fmref_entry;
  GapFmacRefEntry *fmref_entry;
  gint32           l_max_persistent_drawable_id;

  if(filename == NULL)
  {
     return (drawable_id);
  }
  if(!g_file_test(filename, G_FILE_TEST_EXISTS))
  {
    return (drawable_id);
  }
  if(fmacContext == NULL)
  {
     return (drawable_id);
  }


  l_max_persistent_drawable_id = GAP_FMCT_MIN_PERSISTENT_DRAWABLE_ID;


  for(fmref_entry = fmacContext->fmref_list; fmref_entry != NULL; fmref_entry = fmref_entry->next)
  {
    if((fmref_entry->ainfo_type == ainfo_type)
    && (fmref_entry->frame_nr == frame_nr)
    && (fmref_entry->stackposition == stackposition)
    && (fmref_entry->track == track)
    && (strcmp(fmref_entry->filename, filename) == 0))
    {

      return(fmref_entry->persistent_drawable_id);
    }
    l_max_persistent_drawable_id = MAX(l_max_persistent_drawable_id, fmref_entry->persistent_drawable_id);
  }


  new_fmref_entry = g_new(GapFmacRefEntry, 1);

  if(force_id)
  {
    new_fmref_entry->persistent_drawable_id = drawable_id;
  }
  else
  {
    new_fmref_entry->persistent_drawable_id = l_max_persistent_drawable_id + 1;
  }
  new_fmref_entry->ainfo_type = ainfo_type;
  new_fmref_entry->frame_nr = frame_nr;
  new_fmref_entry->stackposition = stackposition;
  new_fmref_entry->track = track;
  new_fmref_entry->mtime = gap_file_get_mtime(filename);
  g_snprintf(new_fmref_entry->filename, sizeof(new_fmref_entry->filename), "%s", filename);


  new_fmref_entry->next = fmacContext->fmref_list;
  fmacContext->fmref_list = new_fmref_entry;

  gap_fmct_save_GapFmacContext(fmacContext);

  return(new_fmref_entry->persistent_drawable_id);

}
