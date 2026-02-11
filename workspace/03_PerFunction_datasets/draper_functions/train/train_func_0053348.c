find_num_type()
{
  DBUG_ENTER("Item_func_num1::find_num_type");
  DBUG_PRINT("info", ("name %s", func_name()));
  switch (hybrid_type= args[0]->result_type()) {
  case INT_RESULT:
    unsigned_flag= args[0]->unsigned_flag;
    break;
  case STRING_RESULT:
  case REAL_RESULT:
    hybrid_type= REAL_RESULT;
    max_length= float_length(decimals);
    break;
  case DECIMAL_RESULT:
    break;
  default:
    DBUG_ASSERT(0);
  }
  DBUG_PRINT("info", ("Type: %s",
                      (hybrid_type == REAL_RESULT ? "REAL_RESULT" :
                       hybrid_type == DECIMAL_RESULT ? "DECIMAL_RESULT" :
                       hybrid_type == INT_RESULT ? "INT_RESULT" :
                       "--ILLEGAL!!!--")));
  DBUG_VOID_RETURN;
}
