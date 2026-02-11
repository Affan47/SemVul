CanonOneStructureINChI(INCHIGEN_CONTROL *genctl, int iINChI, INCHI_IOSTREAM *inp_file)
{
int i,  nRet = 0;

STRUCT_DATA *sd = &(genctl->StructData);

INPUT_PARMS *ip = &(genctl->InpParms);
INCHI_IOSTREAM *output_file = genctl->inchi_file, *log_file = genctl->inchi_file+1;
INCHI_IOSTREAM prbstr, *prb_file=&prbstr;

ORIG_ATOM_DATA *prep_inp_data = &(genctl->PrepInpData[0]);
PINChI2 **pINChI2 = genctl->pINChI;
PINChI_Aux2 **pINChI_Aux2 = genctl->pINChI_Aux;

long num_inp = genctl->num_inp;
char *pStr = genctl->pStr;
int nStrLen = PSTR_BUFFER_SIZE;


    INP_ATOM_DATA *inp_cur_data = NULL;

    INP_ATOM_DATA *inp_norm_data[TAUT_NUM];

    ORIG_ATOM_DATA *cur_prep_inp_data = prep_inp_data + iINChI;

    inchiTime      ulTStart;

    inchi_ios_init(prb_file, INCHI_IOSTREAM_FILE, NULL);

    for (i = 0; i < TAUT_NUM; i ++)
        inp_norm_data[i]=NULL;


    for ( i = 0, nRet = 0; !sd->bUserQuitComponent && i < cur_prep_inp_data->num_components; i ++ )
    {

        if ( ip->msec_MaxTime )
            InchiTimeGet( &ulTStart );


        inp_cur_data = &(genctl->InpCurAtData[iINChI][i]);


        nRet = GetOneComponent( sd, ip, log_file, output_file, inp_cur_data, cur_prep_inp_data,
                                i, num_inp, pStr, nStrLen );

        if ( ip->msec_MaxTime )
            ip->msec_LeftTime -= InchiTimeElapsed( &ulTStart );

        switch ( nRet ) { case _IS_ERROR: case _IS_FATAL: goto exit_cycle; }

#ifndef TARGET_API_LIB

        if ( ip->bDisplay && inp_file != stdin )
        {
            if ( user_quit("Enter=Display Component, Esc=Stop ?", ip->ulDisplTime) )
            {
                sd->bUserQuitComponent = 1;
                break;
            }
        }
#endif


        inp_norm_data[TAUT_NON] = &(genctl->InpNormAtData[iINChI][i]);
        inp_norm_data[TAUT_YES] = &(genctl->InpNormTautData[iINChI][i]);

        nRet = CanonOneComponentINChI(genctl, iINChI, i);


        if ( nRet )
        {
            nRet = TreatCreateOneComponentINChIError(sd, ip, cur_prep_inp_data, i, num_inp,
                                 inp_file, log_file, output_file, prb_file,pStr, nStrLen );
            break;
        }
    }


exit_cycle:

    switch ( nRet )
    {
    case _IS_FATAL:
    case _IS_ERROR: break;
    default:

        break;
    }


    for (i = 0; i < TAUT_NUM; i ++)
        FreeInpAtomData( inp_norm_data[i] );


    return nRet;
}
