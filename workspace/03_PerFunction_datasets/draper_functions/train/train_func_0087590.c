df_word_lr_free (void)
{
  struct df_word_lr_problem_data *problem_data
    = (struct df_word_lr_problem_data *)df_word_lr->problem_data;

  if (df_word_lr->block_info)
    {
      df_word_lr->block_info_size = 0;
      free (df_word_lr->block_info);
      df_word_lr->block_info = NULL;
    }

  BITMAP_FREE (df_word_lr->out_of_date_transfer_functions);
  bitmap_obstack_release (&problem_data->word_lr_bitmaps);
  free (problem_data);
  free (df_word_lr);
}
