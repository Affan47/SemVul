putbuilding(FILE *myfile, tconvdata convdata, tmapdata mapdata, int xpos, int ypos, unsigned char type, int crystals, int id)

{
    int i;
    int mining = 0;


    if( convdata.type == MAP_HL ) { mining = crystals*2; crystals = 0; }

    fprintf(myfile,"[building]\n");


    if( (type+1)/3 == 0 )      fprintf(myfile,"name = 5\n");
    else if( (type+1)/3 == 1 ) fprintf(myfile,"name = 6\n");
    else                       fprintf(myfile,"name = 7\n");


    fprintf(myfile,"type = workshop\n");


    if( (type+1)/3 == 1 )
    {
        fprintf(myfile,"type = factory\n");
        for( i=0 ; i<convdata.maxunits ; i++ )
        {
            if( (mapdata.canbuild[i] == 0) && (strlen(convdata.units[i]) > 0) ) fprintf(myfile,"factory = %s\n",convdata.units[i]);
        }
    }


    if( mining > 0 )
    {
        fprintf(myfile,"mining = %d\n",mining);
    }
    fprintf(myfile,"crystals = %d\n",crystals);
    fprintf(myfile,"player = %i\n",(type+1)%3);
    fprintf(myfile,"id = %d\n",id);
    fprintf(myfile,"pos = %d/%d\n",xpos,ypos);
    fprintf(myfile,"\n");
}
