restore_tmp()
{
  DBUG_PRINT("info", ("restore_tmp this %p tmp_join %p", this, tmp_join));
  DBUG_ASSERT(tmp_join != this);
  memcpy(tmp_join, this, (size_t) sizeof(JOIN));
}
