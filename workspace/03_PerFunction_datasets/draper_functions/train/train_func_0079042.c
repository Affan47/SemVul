write_diff(FILE *f)
   {
      unsigned long long line = 0;
      std::list<struct Change>::reverse_iterator ch;
      for (ch = filechanges.rbegin(); ch != filechanges.rend(); ++ch) {
	 line += ch->offset + ch->del_cnt;
      }

      for (ch = filechanges.rbegin(); ch != filechanges.rend(); ++ch) {
	 std::list<struct Change>::reverse_iterator mg_i, mg_e = ch;
	 while (ch->del_cnt == 0 && ch->offset == 0)
	    ++ch;
	 line -= ch->del_cnt;
	 if (ch->add_cnt > 0) {
	    if (ch->del_cnt == 0) {
	       fprintf(f, "%llua\n", line);
	    } else if (ch->del_cnt == 1) {
	       fprintf(f, "%lluc\n", line+1);
	    } else {
	       fprintf(f, "%llu,%lluc\n", line+1, line+ch->del_cnt);
	    }

	    mg_i = ch;
	    do {
	       dump_mem(f, mg_i->add, mg_i->add_len, NULL);
	    } while (mg_i-- != mg_e);

	    fprintf(f, ".\n");
	 } else if (ch->del_cnt == 1) {
	    fprintf(f, "%llud\n", line+1);
	 } else if (ch->del_cnt > 1) {
	    fprintf(f, "%llu,%llud\n", line+1, line+ch->del_cnt);
	 }
	 line -= ch->offset;
      }
   }
