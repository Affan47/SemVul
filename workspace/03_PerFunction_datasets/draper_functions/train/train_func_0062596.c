ATExecDropNotNull(Relation rel, const char *colName, LOCKMODE lockmode)
{
  HeapTuple	tuple;
  AttrNumber	attnum;
  Relation	attr_rel;
  List	   *indexoidlist;
  ListCell   *indexoidscan;


  attr_rel = heap_open(AttributeRelationId, RowExclusiveLock);

  tuple = SearchSysCacheCopyAttName(RelationGetRelid(rel), colName);

  if (!HeapTupleIsValid(tuple))
    ereport(ERROR,
	    (errcode(ERRCODE_UNDEFINED_COLUMN),
	     errmsg("column \"%s\" of relation \"%s\" does not exist",
		    colName, RelationGetRelationName(rel))));

  attnum = ((Form_pg_attribute) GETSTRUCT(tuple))->attnum;


  if (attnum <= 0)
    ereport(ERROR,
	    (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
	     errmsg("cannot alter system column \"%s\"",
		    colName)));


  indexoidlist = RelationGetIndexList(rel);

  foreach(indexoidscan, indexoidlist)
    {
      Oid			indexoid = lfirst_oid(indexoidscan);
      HeapTuple	indexTuple;
      Form_pg_index indexStruct;
      int			i;

      indexTuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(indexoid));
      if (!HeapTupleIsValid(indexTuple))
	elog(ERROR, "cache lookup failed for index %u", indexoid);
      indexStruct = (Form_pg_index) GETSTRUCT(indexTuple);


      if (indexStruct->indisprimary)
	{


	  for (i = 0; i < indexStruct->indnatts; i++)
	    {
	      if (indexStruct->indkey.values[i] == attnum)
		ereport(ERROR,
			(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
			 errmsg("column \"%s\" is in a primary key",
				colName)));
	    }
	}

      ReleaseSysCache(indexTuple);
    }

  list_free(indexoidlist);


  if (((Form_pg_attribute) GETSTRUCT(tuple))->attnotnull)
    {
      ((Form_pg_attribute) GETSTRUCT(tuple))->attnotnull = FALSE;

      simple_heap_update(attr_rel, &tuple->t_self, tuple);


      CatalogUpdateIndexes(attr_rel, tuple);
    }

  heap_close(attr_rel, RowExclusiveLock);
}
