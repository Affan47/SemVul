model_DS_equal_p( model_DS m1, model_DS m2)
{
   if ((m1->model_file == m2->model_file) &&
       (m1->file_index == m2->file_index) &&
       (db_same_source_p( m1->database, m2->database)))
      return(TRUE);
   else return(FALSE);
}
