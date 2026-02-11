del_strings_and_comments(string& lowline, char& inString) {

    for (unsigned i=0; i<lowline.size(); ++i) {
      if ( inString ) {

        if ( lowline[i] == inString ) {
          lowline[i] = '@';
          ++i;
          if ( i >= lowline.size() ) {

            inString = 0;
            break;
          }
          if ( lowline[i] != inString ) {

            inString = 0;
            continue;
          }
        }
        lowline[i] = '@';
      }

      else if ( lowline[i] == '!' ) {

        for (; i<lowline.size(); ++i) lowline[i] = 'C';
        break;
      }

      else if ( lowline[i] == '\'' || lowline[i] == '\"' ) {
        inString = lowline[i];
        lowline[i] = '@';
      }
    }
  }
