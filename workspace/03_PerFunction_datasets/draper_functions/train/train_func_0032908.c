Write (FILE *file)

	{
	DBInt id;
	DBObjRecord *obj;
	DBObjRecord *record;
	DBObjTableField *field;

	if (DBObjectLIST<DBObjRecord>::Write (file) != DBSuccess) return (DBFault);
	if (FieldPTR->Write (file) != DBSuccess)  return (DBFault);
	for (id = 0;id < FieldPTR->ItemNum ();++id)
		if (FieldPTR->WriteItem (file,id) == DBFault) return (DBFault);

	for (id = 0;id < ItemNum ();++id)
		{
		record = Item (id);
		for (field = FieldPTR->First ();field != (DBObjTableField *) NULL;field = FieldPTR->Next ())
			switch (field->Type ())
				{
				case DBTableFieldTableRec:
				case DBTableFieldDataRec:
					if ((obj = field->Record (record)) != NULL) field->Record (record,(DBObjRecord *) obj->RowID ());
					else field->Record (record,(DBObjRecord *) DBFault);
					break;
				}
		if (WriteItem (file,id) == DBFault) return (DBFault);
		}
	if (MethodPTR->Write (file) != DBSuccess) return (DBFault);
	for (id = 0;id < MethodPTR->ItemNum ();++id) if (MethodPTR->WriteItem (file,id) == DBFault) return (DBFault);
	return (DBSuccess);
	}
