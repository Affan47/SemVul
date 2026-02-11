Unify_Atom_Tagged(WamWord w)
{
  WamWord word, tag_mask;

  if (S != WRITE_MODE)
    {
      DEREF(*S, word, tag_mask);
      S++;

      if (tag_mask == TAG_REF_MASK)
	{
	  Bind_UV(UnTag_REF(word), w);
	  return TRUE;
	}

      return (word == w);
    }

  Global_Push(w);
  return TRUE;
}
