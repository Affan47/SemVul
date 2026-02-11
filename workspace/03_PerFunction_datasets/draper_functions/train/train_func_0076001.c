expand_model( model_DS comp_model)
{
  FILE *model_file_fp, *log_file_fp = NULL, *stream = NULL;
  static fxlstr model_file;
  int file_index, expand_p = TRUE, regenerate_p = FALSE, newlength = 0;
  database_DS database;
  model_DS model = NULL;

  model_file[0] = '\0';

  if (comp_model->compressed_p == FALSE)
    return (comp_model);

  if (make_and_validate_pathname( "model", comp_model->model_file, &model_file,
                                 TRUE) != TRUE)
    exit(1);
  file_index = comp_model->file_index;
  database = expand_database( comp_model->database);

  if ((model = find_model( model_file, file_index, database)) != NULL)
    return (model);
  model_file_fp = fopen( model_file, "r");
  if (read_model_file( model_file_fp, log_file_fp, database, regenerate_p, expand_p,
                      stream, &newlength, model_file) != NULL)
    model = find_model( model_file, file_index, database);
  fclose( model_file_fp);
  return (model);
}
