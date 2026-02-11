extract_sequence_from_file (char* filename, char* acc, char* sequence) {
  FILE* fp;
  int letter;
  int pos = -1;

  if ( (fp = fopen(filename, "r")) == NULL) {
	fprintf (stderr, "Error, cannot open filename %s", filename);
	exit(2);
  }


  if ( (letter = getc(fp)) != '>') {
	fprintf (stderr, "Error, filename %s does contain a fasta sequence beginning with '>'", filename);
	exit(3);
  }
  while ( ((letter = getc(fp)) != EOF) && (letter != ' ' && letter != '\n')) {
	acc[++pos] = letter;
  }
  acc[++pos] = '\0';


  while (letter != '\n') {

	letter = getc(fp);
  }
  pos = -1;
  while ( (letter = getc(fp)) != EOF) {
	if (letter != '\n' && letter != ' ') {
	  sequence[++pos] = letter;
	}
  }
  sequence[++pos] = '\0';

  fclose(fp);
}
