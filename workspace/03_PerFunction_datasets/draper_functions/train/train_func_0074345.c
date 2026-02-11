reverse_complement(string &seq_rc, bool nucleotides_only) {

  reverse(seq_rc.begin(), seq_rc.end());
  for(long i = 0; i < (long)seq_rc.length(); i++) {

    switch(seq_rc[i]) {
    case 'a': seq_rc[i] = 't'; break;
    case 'c': seq_rc[i] = 'g'; break;
    case 'g': seq_rc[i] = 'c'; break;
    case 't': seq_rc[i] = 'a'; break;
    case 'r': seq_rc[i] = 'y'; break;
    case 'y': seq_rc[i] = 'r'; break;
    case 's': seq_rc[i] = 's'; break;
    case 'w': seq_rc[i] = 'w'; break;
    case 'm': seq_rc[i] = 'k'; break;
    case 'k': seq_rc[i] = 'm'; break;
    case 'b': seq_rc[i] = 'v'; break;
    case 'd': seq_rc[i] = 'h'; break;
    case 'h': seq_rc[i] = 'd'; break;
    case 'v': seq_rc[i] = 'b'; break;
    default:
      if(!nucleotides_only) seq_rc[i] = 'n';
      break;
    }
  }
}
