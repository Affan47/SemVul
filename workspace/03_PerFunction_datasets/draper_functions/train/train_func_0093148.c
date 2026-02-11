LoadData(char *filen)
{

    FILE *file;
    NA_Alignment *DataNaAln;
    char temp[1024];


    if(Find2(filen,"gde")!=0)
        strcpy(FileName,filen);

    if (strstr(filen,".arb") || strchr(filen, ':')) {
        if (DataSet == NULL) {
            DataSet = (NA_Alignment *) Calloc(1,
                                              sizeof(NA_Alignment));
            DataNaAln = (NA_Alignment *) DataSet;
            DataSet->rel_offset = 0;
        } else{
            DataNaAln = (NA_Alignment *) DataSet;
        }
        DataType = NASEQ_ALIGN;
        FileFormat = ARBDB;
        LoadFile(filen, DataNaAln,
                 DataType, FileFormat);

        sprintf(temp,"Remote ARBDB access (%s)",filen);
        return;
    }


    if( (file=fopen(filen,"r"))!=0 )
    {
        FindType(filen,&DataType,&FileFormat);
        switch(DataType)
        {
            case NASEQ_ALIGN:
                if(DataSet == NULL)
                {
                    DataSet = (NA_Alignment*)Calloc(1,
                                                    sizeof(NA_Alignment));
                    DataNaAln =(NA_Alignment*)DataSet;
                    DataSet->rel_offset = 0;
                }else{
                    DataNaAln = (NA_Alignment*)DataSet;
                }

                LoadFile(filen,DataNaAln,
                         DataType,FileFormat);

                break;
            default:
                aw_message(GBS_global_string("Internal error: unknown file type of file %s",filen));
                break;
        }
        fclose(file);
    }
    sprintf(temp,"Genetic Data Environment 2.2 (%s)",FileName);
    return;
}
