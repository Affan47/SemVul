next_reads(read_parser::reads_t *rs) {
    for(rs->nb_reads = 0;
        rs->nb_reads < read_parser::reads_t::max_nb_reads && !eof();
        ++rs->nb_reads) {
      read_t *r = &rs->reads[rs->nb_reads];
      r->qual_s = r->qual_e = 0;
      while(sbumpc() != '>')
        BREAK_AT_END;
      BREAK_AT_END;
      r->header = ptr();
      while(sbumpc() != '\n')
        BREAK_AT_END;
      BREAK_AT_END;
      r->hlen  = ptr() - r->header - 1;
      r->seq_s = ptr();

      while(!eof())
        if(sbumpc() == '\n')
          if(speekc() == '>')
            break;
      r->seq_e = ptr();
    }
    return !eof();
  }
