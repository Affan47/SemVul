pnm_component_to_pgm(int block[], int block_no)
{
  int i, row, col;

  if (block_no % 4 == selected_component) {
    for (i = 0; i < 64; i++)
      saved_block[0][saved_block_no][i] = block[i];
    saved_block_no++;
  }

  if (saved_block_no >= 20) {
    saved_block_no = 0;
    for (row = 0; row < 8; row++) {
      for (col = 0; col < 20; col++) {
        for (i = 0; i < 8; i++) {
          fprintf(output_file, "%d ", saved_block[0][col][(row * 8) + i]);
        }
      }
      fprintf(output_file, "\n");
    }
  }
}
