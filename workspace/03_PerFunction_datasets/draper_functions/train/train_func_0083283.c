add_xkbmaplist()
{
    FILE *ifp;
    int i=0,j=0;
    char iline[80];
    char xkfile[65];
    char *ntoken;

    ifp= fopen("/usr/share/X11/xkb/symbols/in", "r");
    while (fgets(iline,80,ifp) != NULL)
    {
        if (strstr(iline,"xkb_symbols")!=NULL)
        {
            ntoken=(char *) malloc(sizeof(char) * 25);
            memset(ntoken,'\0',25);
            ntoken = strtok(iline, " ");
            ntoken = strtok(NULL, " \"");
        }
        if (strstr(iline,"name[Group1]")!=NULL)
        {
            if (strcmp(iline,"\tname[Group1]=\"India\";\n")==0)
            {
                sprintf(xkfile,"xkb-%s", "India");
                gtk_combo_box_text_append_text ((GtkComboBoxText *)combo_mim, xkfile);
                strcpy(lout[addmap].l_name,xkfile);
                addmap++;
                maplist[mimcnt]= (char *) malloc(strlen(xkfile)+1);
                strcpy(maplist[mimcnt++],xkfile);
            }
            if (strcmp(iline,"\tname[Group1]=\"India\";\n")!=0)
            {
                char *itoken,*nntoken;
                size_t nn=0,nn_cnt=0;
                itoken=(char *)malloc(65*sizeof(char));
                memset(itoken,'\0',65);

                nn=strlen(iline);
                while (nn_cnt < nn)
                {
                    if (iline[nn_cnt] == '\"')
                    {
                        strncpy(itoken,iline+nn_cnt+1,nn-nn_cnt-4);
                        break;
                    }
                    else
                        nn_cnt++;
                }
                sprintf(xkfile,"xkb-%s", itoken);
                if (strstr(xkfile,"typewriter")==NULL && strstr(xkfile, "Urdu")==NULL && strstr(xkfile, "English")==NULL)
                {
                    gtk_combo_box_text_append_text ((GtkComboBoxText *)combo_mim, xkfile);
                    strcpy(lout[addmap].l_name,xkfile);
                    addmap++;
                    maplist[mimcnt]= (char *) malloc(strlen(xkfile)+1);
                    strcpy(maplist[mimcnt++],xkfile);
                }
            }
        }
    }
}
