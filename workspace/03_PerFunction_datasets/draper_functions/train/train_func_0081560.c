destroy()
{
  DBUG_ENTER("Query_cache_block::destroy");
  DBUG_PRINT("qcache", ("destroy block 0x%lx, type %d",
			(ulong) this, type));
  type = INCOMPLETE;
  DBUG_VOID_RETURN;
}
