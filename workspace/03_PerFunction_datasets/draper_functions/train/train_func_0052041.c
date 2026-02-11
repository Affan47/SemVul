Set_Info_Struct(CALL **Info, char *String)
{
	int Cnt = 0;
	int channel;
	char** Array = String_to_Array(String,C_DELIMITER);

	while(Array[Cnt++]);

	if (Cnt-1 != PROT_ELEMENTS)
	{
		del_Array(Array);
		fprintf(stderr,"Internal error: wrong structure (%d elements), %d expected!\n",Cnt, PROT_ELEMENTS);
		return -1;
	}

	if (*Info == NULL)
		if (((*Info) = (CALL*) calloc(1,sizeof(CALL))) == NULL)
			return NO_MEMORY;

	Cnt = 0;

  channel = atoi(Array[Cnt++]);
  (*Info)->stat = atoi(Array[Cnt++]);
  (*Info)->dialin = atoi(Array[Cnt++]);
	strcpy((*Info)->num[_ME((*Info))],Array[Cnt++]);
  strcpy((*Info)->alias[_ME((*Info))],Array[Cnt++]);
	strcpy((*Info)->num[_OTHER((*Info))],Array[Cnt++]);
  strcpy((*Info)->vorwahl[_OTHER((*Info))],Array[Cnt++]);
  strcpy((*Info)->rufnummer[_OTHER((*Info))],Array[Cnt++]);
  strcpy((*Info)->alias[_OTHER((*Info))],Array[Cnt++]);
  strcpy((*Info)->area[_OTHER((*Info))],Array[Cnt++]);
  (*Info)->connect = atoi(Array[Cnt++]);
  (*Info)->t_duration = atoi(Array[Cnt++]);
  (*Info)->aoce = atoi(Array[Cnt++]);
  strcpy((*Info)->money,Array[Cnt++]);
  strcpy((*Info)->currency,Array[Cnt++]);
  (*Info)->ibytes = atoi(Array[Cnt++]);
  (*Info)->obytes = atoi(Array[Cnt++]);
  (*Info)->ibps = atof(Array[Cnt++]);
  (*Info)->obps = atof(Array[Cnt++]);
  strcpy((*Info)->msg,Array[Cnt++]);

	del_Array(Array);
	return channel;
}
