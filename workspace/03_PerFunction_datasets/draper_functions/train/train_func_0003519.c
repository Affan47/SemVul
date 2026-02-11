initialize_bismark_id() {
  FILE* handle = fopen(BISMARK_ID_FILENAME, "r");
  if (!handle) {
    perror("Cannot open Bismark ID file " BISMARK_ID_FILENAME);
    exit(1);
  }
  if(fscanf(handle, "%255s\n", bismark_id) < 1) {
    perror("Cannot read Bismark ID file " BISMARK_ID_FILENAME);
    exit(1);
  }
  fclose(handle);
}
