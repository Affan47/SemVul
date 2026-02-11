Unify_Nil(void)
{
  WamWord word, tag_mask;

  if (S != WRITE_MODE)
    {
      DEREF(*S, word, tag_mask);
      S++;
      if (tag_mask == TAG_REF_MASK)
	{
	  Bind_UV(UnTag_REF(word), NIL_WORD);
	  return TRUE;
	}

      return (word == NIL_WORD);
    }

  Global_Push(NIL_WORD);
  return TRUE;
}
