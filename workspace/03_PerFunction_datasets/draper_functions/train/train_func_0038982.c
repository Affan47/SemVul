align_NASTy (ntCounts* templateSeq, int templateSeqLength, char* querySeq, char* templateAlignment, char* queryAlignment) {

  int querySeqLength = strlen(querySeq);

  if (DEBUG) {
	fprintf (stdout, "lengths:\ntemplate: %d\nquery: %d\n\n", templateSeqLength, querySeqLength);
  }

  int x = templateSeqLength;
  int y = querySeqLength;

  Cell** matrix = build_matrix(x, y);
  populate_matrix(matrix, x, y, templateSeq, querySeq);

  Point p = get_highest_scoring_cell_coordinates(matrix, x, y);

  extract_aligned_sequences(matrix, x, y, p, templateSeq, querySeq, templateAlignment, queryAlignment);


}
