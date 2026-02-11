mtrie_makenewbranch(Mergertrierep *trierep,
                                     Suffixinfo *suffixinfo,
                                     unsigned long currentdepth,
                                     Mergertrienode *oldnode)
{
  Mergertrienode *newbranch, *newleaf;
  GtUchar cc1, cc2;
  Encseqreadinfo *eri = trierep->encseqreadinfo + suffixinfo->idx;

#ifdef WITHTRIEIDENT
#ifdef WITHTRIESHOW
  printf("makenewbranch(ident=" Formatuint64_t ")\n",
          PRINTuint64_tcast(suffixinfo->ident));
#endif
#endif
  newbranch = newMergertrienode(trierep);
  newbranch->suffixinfo = *suffixinfo;
  newbranch->rightsibling = oldnode->rightsibling;
  cc1 = getfirstedgechar(trierep,oldnode,currentdepth);
  if (suffixinfo->startpos + currentdepth >=
      gt_encseq_total_length(eri->encseqptr))
  {
    cc2 = (GtUchar) SEPARATOR;
  } else
  {
    cc2 = gt_encseq_get_encoded_char(eri->encseqptr,
                         suffixinfo->startpos + currentdepth,
                         eri->readmode);
  }
  newleaf = mtrie_makenewleaf(trierep,suffixinfo);
  if (mtrie_comparecharacters(cc1,oldnode->suffixinfo.idx,
                        cc2,suffixinfo->idx) <= 0)
  {
    makesuccs(newbranch,oldnode,newleaf);
  } else
  {
    makesuccs(newbranch,newleaf,oldnode);
  }
  newbranch->depth = currentdepth;
  return newbranch;
}
