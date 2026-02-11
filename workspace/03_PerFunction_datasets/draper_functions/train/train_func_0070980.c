fix_length_and_dec()
{
  DBUG_ENTER("Item_func_neg::fix_length_and_dec");
  Item_func_num1::fix_length_and_dec();


  if (hybrid_type == INT_RESULT && args[0]->const_item())
  {
    longlong val= args[0]->val_int();
    if ((ulonglong) val >= (ulonglong) LONGLONG_MIN &&
        ((ulonglong) val != (ulonglong) LONGLONG_MIN ||
          args[0]->type() != INT_ITEM))
    {


      hybrid_type= DECIMAL_RESULT;
      DBUG_PRINT("info", ("Type changed: DECIMAL_RESULT"));
    }
  }
  unsigned_flag= 0;
  DBUG_VOID_RETURN;
}
