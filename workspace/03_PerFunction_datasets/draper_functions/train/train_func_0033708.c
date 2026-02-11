initSWtable(GtSWtable *swtable,
                        unsigned long totallength,
                        GtEncseqAccessType sat,
                        unsigned long items)
{
  switch (sat)
  {
    case GT_ACCESS_TYPE_UCHARTABLES:
      swtable->st_uchar.maxrangevalue = (unsigned long) UCHAR_MAX;
      swtable->st_uchar.numofpages
        = totallength/swtable->st_uchar.maxrangevalue + 1;
      swtable->st_uchar.numofpositionstostore = items;
      break;
    case GT_ACCESS_TYPE_USHORTTABLES:
      swtable->st_uint16.maxrangevalue = (unsigned long) USHRT_MAX;
      swtable->st_uint16.numofpages
        = totallength/swtable->st_uint16.maxrangevalue + 1;
      swtable->st_uint16.numofpositionstostore = items;
      break;
    case GT_ACCESS_TYPE_UINT32TABLES:
      swtable->st_uint32.maxrangevalue = (unsigned long) UINT32_MAX;
      swtable->st_uint32.numofpages
        = totallength/swtable->st_uint32.maxrangevalue + 1;
      swtable->st_uint32.numofpositionstostore = items;
      break;
    default:
      fprintf(stderr,"initSWtable(sat = %s is undefined)\n",
                     gt_encseq_access_type_str(sat));
      exit(GT_EXIT_PROGRAMMING_ERROR);
  }
}
