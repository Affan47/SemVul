frag_grow (unsigned int nchars)
{
  if (obstack_room (&frchain_now->frch_obstack) < nchars)
    {
      long oldc;
      long newc;


      if (nchars < 0x10000)
        newc = 2 * nchars;
      else
        newc = nchars + 0x10000;
      newc += SIZEOF_STRUCT_FRAG;


      if (newc < 0)
        as_fatal (_("can't extend frag %u chars"), nchars);


      oldc = obstack_chunk_size (&frchain_now->frch_obstack);
      if (newc > oldc)
	obstack_chunk_size (&frchain_now->frch_obstack) = newc;

      while (obstack_room (&frchain_now->frch_obstack) < nchars)
        {


          frag_wane (frag_now);
          frag_new (0);
        }


      obstack_chunk_size (&frchain_now->frch_obstack) = oldc;
    }
}
