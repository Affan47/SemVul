ntx_add(char **tags)
{
  char file[FILE_MAX], note[SUMREC_LENGTH];
  char **ptr, *tmp;
  unsigned int num;
  exception_t exc;

  srand(time(NULL));
  num = rand() & 0xffff;

  while(1) {
    FILE *nout = NULL;

    seprintf(file, FILE_MAX, NOTES_DIR"/%04x", num);
    try nout = raw_open(file, "r");
    catch(exc) if(exc.type == E_FACCESS) break;
    release(nout);
    num = (num + 1) & 0xffff;
  }


  ntx_editor(file);


  try ntx_summary(file, note + SUMMARY_OFFSET);
  catch(exc) {
    if((exc.type == E_FACCESS || exc.type == E_INVAL) &&
       strcmp(file, exc.value) == 0) {
      fputs("No new note was recorded.\n", stderr);
      remove(file);
      exit(EXIT_SUCCESS);
    } else throw(exc.type, exc.value);
  }


  strncpy(note, file + strlen(NOTES_DIR) + 1, ID_LENGTH);
  note[4] = ID_SEP;

  for(ptr = tags; *ptr != NULL; ptr++) {
    seprintf(file, FILE_MAX, TAGS_DIR"/%s", *ptr);
    ntx_append(file, note);
  }


  ntx_append(INDEX_FILE, note);


  seprintf(file, FILE_MAX, REFS_DIR"/%.2s", note);
  tmp = ntx_tagstolist(note, tags);
  ntx_append(file, tmp);
  release(tmp);


  fputs(note, stdout);
}
