Read(FILE* f)
{
  WordReference word;
#define WORD_BUFFER_SIZE	1024
  char buffer[WORD_BUFFER_SIZE + 1];
  String line;
  int line_number = 0;
  int inserted = 0;

  while(fgets(buffer, WORD_BUFFER_SIZE, f)) {
    line_number++;
    int buffer_length = strlen(buffer);
    int eol = buffer[buffer_length - 1] == '\n';

    if(eol) buffer[--buffer_length] = '\0';

    line.append(buffer, buffer_length);


    if(!eol) continue;


    if(line.last() == '\\') {
      line.chop(1);
      continue;
    }

    if(!line.empty()) {
      if(word.Set(line) != OK) {
	fprintf(stderr, "WordList::Read: line %d : %s\n", line_number, (char*)line);
	fprintf(stderr, " cannot build WordReference (ignored)\n");
      } else {
	if(Insert(word) != OK) {
	  fprintf(stderr, "WordList::Read: line %d : %s\n", line_number, (char*)line);
	  fprintf(stderr, " insert failed (ignored)\n");
	} else {
	  inserted++;
	}
	if(verbose) fprintf(stderr, "WordList::Read: inserting %s\n", (char*)word.Get());
      }

      line.trunc();
    }
  }
  return inserted;
}
