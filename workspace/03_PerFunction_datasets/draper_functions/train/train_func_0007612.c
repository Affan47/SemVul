LineContainsImport(const int line, Accessor &styler) const {
      if (options.foldImports) {
         int currentPos = styler.LineStart(line);
         int style = styler.StyleAt(currentPos);

         int eol_pos = styler.LineStart(line + 1) - 1;

         while (currentPos < eol_pos) {
            int ch = styler[currentPos];
            style = styler.StyleAt(currentPos);

            if (ch == ' ' || ch == '\t'
             || IsCommentBlockStyle(style)
             || style == SCE_HA_LITERATE_CODEDELIM) {
               currentPos++;
            } else {
               break;
            }
         }

         return (style == SCE_HA_KEYWORD
              && styler.Match(currentPos, "import"));
      } else {
         return false;
      }
   }
