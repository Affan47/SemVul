CreateGLLump(const char *name)
{
  lump_t *cur;
  lump_t *gl_level;

# if DEBUG_DIR
  PrintDebug("Create GL Lump... %s\n", name);
# endif


  if (! wad.current_level->lev_info->buddy)
    CreateGLMarker();

  gl_level = wad.current_level->lev_info->buddy;


  for (cur=gl_level->lev_info->children; cur; cur=cur->next)
  {
    if (strcmp(name, cur->name) == 0)
      break;
  }

  if (cur)
  {
    if (cur->data)
      UtilFree(cur->data);

    cur->data = NULL;
    cur->length = 0;
    cur->space  = 0;

    return cur;
  }


  cur = NewLump(UtilStrDup(name));


  cur->next = gl_level->lev_info->children;
  cur->prev = NULL;

  if (cur->next)
    cur->next->prev = cur;

  gl_level->lev_info->children = cur;

  return cur;
}
