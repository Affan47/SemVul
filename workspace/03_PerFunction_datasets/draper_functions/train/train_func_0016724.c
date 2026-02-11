embPdbListHeterogens(const AjPPdb pdb, AjPList *list_heterogens,
			    AjPInt *siz_heterogens, ajint *nhet,
			    AjPFile logfile)
{


    AjIList iter  = NULL;
    AjPAtom hetat = NULL;
    ajuint i = 0U;
    ajint prev_gpn = -10000;

    AjPList GrpAtmList = NULL;

    AjPAtom *AtmArray  = NULL;
    ajint n=0;
    ajint grp_count = 0;
    ajint arr_count = 0;


    if((pdb==NULL)||(list_heterogens==NULL)||(siz_heterogens==NULL))
    {
        ajWarn("Bad args passed to embPdbListHeterogens\n");

        return ajFalse;
    }

    if((!(*list_heterogens))||(!(*siz_heterogens)))
    {
        ajWarn("Bad args passed to embPdbListHeterogens\n");

        return ajFalse;
    }

    if(pdb->Ngp>0)
        ajFmtPrintF(logfile, "\tNGP:%d\n", pdb->Ngp);

    if(pdb->Nchn>0)
    {
        for(i = 0U; i < pdb->Nchn; i++)
        {
            prev_gpn=-100000;

            iter=ajListIterNewread(pdb->Chains[i]->Atoms);


            while((hetat=(AjPAtom)ajListIterGet(iter)))
            {

                if(hetat->Type != 'H')
                    continue;


                if(prev_gpn != hetat->Gpn)
                {
                    grp_count++;

                    if(GrpAtmList)
                    {
                        n=(ajuint) (ajListToarray(GrpAtmList, (void ***) &AtmArray));
                        ajListPushAppend(*list_heterogens, AtmArray);


                        AtmArray=NULL;
                        ajIntPut(siz_heterogens, arr_count, n);
                        (*nhet)++;
                        ajListFree(&GrpAtmList);
                        GrpAtmList=NULL;
                        arr_count++;
                    }

                    GrpAtmList=ajListNew();
                    prev_gpn=hetat->Gpn;
                }

                ajListPushAppend(GrpAtmList, (AjPAtom) hetat);
            }


            ajListIterDel(&iter);

        }

        if(GrpAtmList)
        {
            n=(ajuint) (ajListToarray(GrpAtmList, (void ***) &AtmArray));
            ajListPushAppend(*list_heterogens, AtmArray);


            AtmArray=NULL;
            ajIntPut(siz_heterogens, arr_count, n);
            (*nhet)++;
            ajListFree(&GrpAtmList);
            GrpAtmList=NULL;
        }

        GrpAtmList = NULL;
        prev_gpn   = -10000;

    }


    return ajTrue;
}
