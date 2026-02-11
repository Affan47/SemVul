CON_evaluatestatistic(char   *&result,int **statistic,char **groupflags,
                           char    *groupnames,int alignlength,double fupper,int lower,
                           double   fconsidbound,int gapbound,int countgap,int numgroups )
{
    int row=0;
    int j = 0;
    int groupfr[MAX_GROUPS];
    int highestfr,highestgr;
    long numentries;

    aw_status("calculating result");

    result=(char *)GB_calloc(alignlength+1,1);

    for(int column=0;column<alignlength;column++){
        numentries=0;
        for (row=0;statistic[row];row++)  numentries+=statistic[row][column];
        if (numentries==0) {
            result[column]='.';
            continue;
        }

        if(numentries-statistic[0][column]==0) {
            result[column]='=';
            continue;
        }

        if(!countgap)  {
            numentries -= statistic[0][column];
            statistic[0][column]=0;
        }

        if((statistic[0][column]*100/numentries)>gapbound) {
            result[column]='-';
            continue;
        }

        for(j=0;j<numgroups;j++) {
            groupfr[j]=0;
        }

        row=0;
        while(statistic[row])   {
            if((statistic[row][column]*100.0)>=fconsidbound*numentries){
                for(j=numgroups-1;j>=0;j--){
                    if(groupflags[j][row]){
                        groupfr[j]+= statistic[row][column];
                    }
                }
            }
            row++;
        }

        highestfr=0;highestgr=0;
        for(j=0;j<numgroups;j++){
            if(groupfr[j] > highestfr){
                highestfr=groupfr[j];
                highestgr=j;
            }
        }

        if((highestfr*100.0/numentries)>=fupper)  {
            result[column]=groupnames[highestgr];
        } else if((highestfr*100/numentries)>=lower){
            char c=groupnames[highestgr];
            if(c>='A' && c<='Z') {
                c=c-'A'+'a';
            }
            result[column]=c;
        } else {
            result[column]='.';
        }
    }
}
