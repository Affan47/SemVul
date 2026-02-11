write_rawmap(FILE *myfile, tconvdata convdata, tmapdata mapdata, int skip)

{
    int x,y;


    int maxx = mapdata.mapx, maxy = mapdata.mapy;
    if( skip > 0 ) { maxx--; maxy--; }


    fprintf(myfile,"[map-raw]\n");
    for( y=0; y<maxy ; y++ )
    {
        for ( x=0 ; x<maxx ; x++ ) fprintf(myfile,"%3.3d,",convdata.rawtiles[ mapdata.map[y*mapdata.mapx+x].terrain ]);
        fprintf(myfile,"\n");
    }
    fprintf(myfile,"\n");
}
