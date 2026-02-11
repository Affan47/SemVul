set_current_line(const char *index, const char *line)
{
  if (word_iterator.current_line) {
    free(word_iterator.current_line);
    word_iterator.current_line = NULL;
  }
  if (line) {
    word_iterator.current_line = strdup(line);
  }
  if (word_iterator.current_index) {
    free(word_iterator.current_index);
    word_iterator.current_index = NULL;
  }
  if (index) {
    word_iterator.current_index = strdup(index);
  }
}
