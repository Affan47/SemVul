free_all_code(context_type* context, int num_methods, unsigned char** code)
{
  int i;
  for (i = 0; i < num_methods; ++i) {
      if (code[i] != NULL) {
          pop_and_free(context);
      }
  }
  pop_and_free(context);
  pop_and_free(context);
}
