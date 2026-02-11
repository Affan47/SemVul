blindtrie_copy_either(GtBlindtrie *blindtrie,
                                  GtBlindtriesnodeptr destnode,
                                  GtBlindtriesnodeptr srcnode)
{
  gt_assert(destnode < blindtrie->nextfreeBlindtrienode &&
            srcnode < blindtrie->nextfreeBlindtrienode);
  blindtrie->spaceBlindtrienode[destnode].either1
    = blindtrie->spaceBlindtrienode[srcnode].either1;
  blindtrie->spaceBlindtrienode[destnode].either2
    = blindtrie->spaceBlindtrienode[srcnode].either2;
}
