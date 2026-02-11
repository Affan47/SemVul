MFVarGetInt (int id,int itemID, int missingVal) {
	int val;
	MFVariable_t *var;

	if (((var = MFVarGetByID (id)) == (MFVariable_t *) NULL) || (itemID < 0) || (itemID >= var->Header.ItemNum)) {
		CMmsgPrint (CMmsgAppError,"Error: Invalid variable [%d,%d] in: %s:%d\n",id,itemID,__FILE__,__LINE__);
		return (MFDefaultMissingInt);
	}

	if (var->Set != true) CMmsgPrint (CMmsgWarning,"Warning: Unset variable %s\n",var->Name);
	if (_MFVarTestMissingVal (var,itemID)) return (missingVal);

	switch (var->Header.DataType) {
		case MFByte:	val = (int) (((char *)   var->Data) [itemID]); break;
		case MFShort:	val = (int) (((short *)  var->Data) [itemID]); break;
		case MFInt:		val = (int) (((int *)    var->Data) [itemID]); break;
		case MFFloat:	val = (int) (((float *)  var->Data) [itemID]); break;
		case MFDouble:	val = (int) (((double *) var->Data) [itemID]); break;
		default:
			CMmsgPrint (CMmsgAppError,"Error: Invalid variable [%s,%d] type [%d] in %s:%d\n",var->Name, itemID, var->Header.DataType,__FILE__,__LINE__);
			return (MFDefaultMissingInt);
	}
	return (var->Flux ? (val / var->NStep) : val);
}
