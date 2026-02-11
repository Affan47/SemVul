fill() {
    bucket_t *new_seq = 0;

    while(true) {
      if(!new_seq) {
        new_seq = write_next();
        if(!new_seq)
          break;
      }
      new_seq->end = new_seq->start + buffer_size;
      char *start = new_seq->start;
      if(have_seam) {
        have_seam = false;
        memcpy(start, seam, 2 * (mer_len - 1));
        start += 2 * (mer_len - 1);
      }
      bool input_eof = !fparser->parse(start, &new_seq->end);
      if(new_seq->end > new_seq->start + 2 * mer_len) {
        have_seam = true;
        memcpy(seam, new_seq->end - 2 * (mer_len - 1), 2 * (mer_len - 1));
        write_release(new_seq);
        new_seq = 0;
      }
      if(input_eof) {
        delete fparser;
        have_seam = false;
        if(++current_file == files.end()) {
          close();
          break;
        }
        fparser = seq_qual_parser::new_parser(*current_file);
      }
    }
  }
