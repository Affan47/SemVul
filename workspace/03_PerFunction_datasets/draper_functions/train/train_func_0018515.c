send_error(uint errcode,const char *err)
{
  DBUG_ENTER("multi_delete::send_error");


  my_message(errcode, err, MYF(0));

  DBUG_VOID_RETURN;
}
