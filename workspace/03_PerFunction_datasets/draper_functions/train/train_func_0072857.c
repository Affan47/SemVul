cbf_flush_characters (cbf_file *file)
{
  int done;

  if (!file)

    return CBF_ARGUMENT;


  if (file->characters_used == 0)

    return 0;


  if (file->digest)

    MD5Update (file->digest, file->characters, file->characters_used);

  while (file->temporary) {

    file->characters += file->characters_used;

    file->characters_size -= file->characters_used;

    file->characters_used = 0;


    if (file->characters_size < CBF_INIT_WRITE_BUFFER )  {

      size_t old_data, old_size;

      char ** fc;

      fc = &(file->characters_base);

      old_data = file->characters-file->characters_base;

      old_size = old_data + file->characters_size;

      if (cbf_realloc ((void **)fc, &old_size, 1, old_size*2)) {

        file->temporary = 0;

        file->characters = file->characters_base;

        file->characters_used = old_data;

        file->characters_size = old_size;

        break;

      } else {

        file->characters = file->characters_base + old_data;

        file->characters_size = old_size - old_data;

      }

    }

    return 0;

  }

  done = fwrite (file->characters, 1, file->characters_used, file->stream);


  if (done > 0)

    fflush (file->stream);


  if (done < file->characters_used)
  {
    if (done > 0)
    {
      memmove (file->characters, file->characters + done,
        file->characters_size - done);

      file->characters_used = file->characters_size - done;
    }

    return CBF_FILEWRITE;
  }

  file->characters_used = 0;


  return 0;
}
