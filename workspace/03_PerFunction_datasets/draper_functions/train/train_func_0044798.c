PT_LoadCache__Arc(PT_Index index_, const char *filename) {
  if (index_ != NULL && filename != NULL) {
    PT_Index__Arc index = &index_->slots.formatArc;

    index->timestamp = file_timestamp(filename);
    MutexInit(&index->fileLock);
    index->file = fopen(filename, "rb");


    if (index->file != NULL) {
      inthash hashtable = index->hash;

      if (readArcURLRecord(index) == 0) {
        int entries = 0;


        if (strncmp(index->line, "filedesc://", sizeof("filedesc://") - 1) != 0) {
          fprintf(stderr, "Unexpected bad signature #%s" LF, index->line);
          fclose(index->file);
          index->file = NULL;
          return 0;
        }

        index->timestamp = getArcTimestamp(index->line);

        if (skipArcData(index->file, index->line) != 0
            || skipArcNl(index->file) != 0) {
          fprintf(stderr, "Unexpected bad data offset size first entry" LF);
          fclose(index->file);
          index->file = NULL;
          return 0;
        }

        while(!feof(index->file)) {
          unsigned long int fpos = ftell(index->file);

          if (skipArcNl(index->file) == 0 && readArcURLRecord(index) == 0) {
            int length = getArcLength(index->line);

            if (length >= 0) {
              const char *filenameIndex = copyArcField(index->line, 0,
                                                       index->filenameIndexBuff, sizeof(index->filenameIndexBuff) - 1);

              if (strncmp(filenameIndex, "http://", 7) == 0) {
                filenameIndex += 7;
              }
              if (*filenameIndex != 0) {
                if (skipArcData(index->file, index->line) != 0) {
                  fprintf(stderr,
                          "Corrupted cache data entry #%d (truncated file?), aborting read"
                          LF, (int) entries);
                }

                if (PT_CompatibleScheme(index->filenameIndexBuff)) {
                  inthash_add(hashtable, filenameIndex, fpos);
                  entries++;
                }
              } else {
                fprintf(stderr, "Corrupted cache meta entry #%d" LF,
                        (int) entries);
              }
            } else {
              fprintf(stderr,
                      "Corrupted cache meta entry #%d, aborting read" LF,
                      (int) entries);
              break;
            }
          } else {
            break;
          }
        }


        return 1;
      } else {
        fprintf(stderr, "Bad file (empty ?)" LF);
      }
    } else {
      fprintf(stderr, "Unable to open file" LF);
      index = NULL;
    }
  } else {
    fprintf(stderr, "Bad arguments" LF);
  }
  return 0;
}
