gt_mmsearch_extendright(const GtEncseq *dbencseq,
                                             GtEncseqReader *esr,
                                             GtReadmode readmode,
                                             unsigned long totallength,
                                             unsigned long dbend,
                                             const GtQuerysubstring
                                               *querysubstring,
                                             unsigned long matchlength)
{
  GtUchar dbchar;
  unsigned long dbpos, querypos;

  if (dbend < totallength)
  {
    gt_encseq_reader_reinit_with_readmode(esr,dbencseq,readmode,dbend);
  }
  for (dbpos = dbend, querypos = querysubstring->offset + matchlength;
       dbpos < totallength &&
       querypos < querysubstring->queryrep->length;
       dbpos++, querypos++)
  {
    dbchar = gt_encseq_reader_next_encoded_char(esr);
    if (ISSPECIAL(dbchar) ||
        dbchar != gt_mmsearch_accessquery(querysubstring->queryrep,querypos))
    {
      break;
    }
  }
  return dbpos - dbend;
}
