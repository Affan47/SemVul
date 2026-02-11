zchar_storage_finish()
{
  TRACE_LOG("zchar_storage_word_index: %d.\n", zchar_storage_word_index);
  if (zchar_storage_word_index == 0)
  {


    if (zchar_storage_output_index != zchar_storage_output)
    {


      TRACE_LOG("Successfully finalized full word.");
      *(zchar_storage_output_index-2) |= 0x80;
    }
    else
    {


      if (zchar_storage_output_index >= zchar_storage_index_behind)
      {
        TRACE_LOG("zchar_storage_finish ran out of space.\n");
        return -1;
      }

      TRACE_LOG("zchar: storing word %x at %x.\n",
          zchar_storage_word, 0x94a5);
      store_word(zchar_storage_output, 0x94a5);
    }
  }
  else
  {


    if (zchar_storage_output_index >= zchar_storage_index_behind)
    {
      TRACE_LOG("zchar_storage_finish ran out of space.\n");
      return -1;
    }

    if (zchar_storage_word_index == 1)
      zchar_storage_word |= (5 << 5);

    zchar_storage_word |= 0x8005;

    TRACE_LOG("zchar: storing word %x at %x.\n",
        zchar_storage_word, zchar_storage_output_index);
    store_word(zchar_storage_output_index, zchar_storage_word);
  }

  return 0;
}
