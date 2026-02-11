digest_word_file (const char *file_name, WORD_TABLE *table)
{
  BLOCK file_contents;
  char *cursor;
  char *word_start;

  swallow_file_in_memory (file_name, &file_contents);

  table->start = NULL;
  table->alloc = 0;
  table->length = 0;


  cursor = file_contents.start;
  while (cursor < file_contents.end)
    {


      word_start = cursor;
      while (cursor < file_contents.end && *cursor != '\n')
        cursor++;


      if (cursor > word_start)
        {
          if (table->length == table->alloc)
            {
              if ((SIZE_MAX / sizeof *table->start - 1) / 2 < table->alloc)
                xalloc_die ();
              table->alloc = table->alloc * 2 + 1;
              table->start = xrealloc (table->start,
                                       table->alloc * sizeof *table->start);
            }

          table->start[table->length].start = word_start;
          table->start[table->length].size = cursor - word_start;
          table->length++;
        }


      if (cursor < file_contents.end)
        cursor++;
    }


  qsort (table->start, table->length, sizeof table->start[0], compare_words);
}
