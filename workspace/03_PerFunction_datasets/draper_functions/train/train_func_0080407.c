parse_seq_id(ESL_SQNCBI_DATA *ncbi)
{
  int   status;
  int  *id_ptr;

  unsigned char c;


  if (parse_expect(ncbi, "\x30\x80", 2) != eslOK)           return eslEFORMAT;

  if (parse_consume(ncbi, &c, 1) != eslOK)                  return eslEFORMAT;


  while (c != 0x00) {
    if (parse_expect(ncbi, "\x80", 1) != eslOK)             return eslEFORMAT;
    switch (c) {
    case 0xa0:
      status = parse_object_id(ncbi);
      break;
    case 0xa1:
      id_ptr = (ncbi->int_id != -1) ? NULL : &ncbi->int_id;
      status = parse_integer(ncbi, id_ptr);
      break;
    case 0xa2:
      status = parse_integer(ncbi, NULL);
      break;
    case 0xa3:
      status = parse_giimport_id(ncbi);
      break;
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
      status = parse_textseq_id(ncbi);
      break;
    case 0xa8:
      status = parse_patent_seq_id(ncbi);
      break;
    case 0xa9:
      status = parse_textseq_id(ncbi);
      break;
    case 0xaa:
      status = parse_dbtag(ncbi);
      break;
    case 0xab:
      status = parse_integer(ncbi, NULL);
      break;
    case 0xac:
    case 0xad:
      status = parse_textseq_id(ncbi);
      break;
    case 0xae:
      status = parse_pdb_seq_id(ncbi);
      break;
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
      status = parse_textseq_id(ncbi);
      break;
    default:
      status = eslEFORMAT;
    }

    if (status != eslOK)                                    return status;
    if (parse_expect(ncbi, "\x00\x00", 2) != eslOK)         return eslEFORMAT;
    if (parse_consume(ncbi, &c, 1)        != eslOK)         return eslEFORMAT;
  }


  if (c != 0x00 || parse_expect(ncbi, "\x00", 1) != eslOK)  return eslEFORMAT;

  return eslOK;
}
