print_hex (unsigned char *bytes, unsigned int len, int depth)
{
  int i, columns;

  fprintf(stderr, "array of bytes [\n");

  indent (depth + 1);


  columns = (80 - ((depth + 1) * INDENT)) / 3;

  if (columns < 8)
    columns = 8;

  i = 0;

  while (i < len)
    {
      fprintf(stderr, "%02x", bytes[i]);
      i++;

      if (i != len)
        {
          if (i % columns == 0)
            {
              fprintf(stderr, "\n");
              indent (depth + 1);
            }
          else
            {
              fprintf(stderr, " ");
            }
        }
    }

  fprintf(stderr, "\n");
  indent (depth);
  fprintf(stderr, "]\n");
}
