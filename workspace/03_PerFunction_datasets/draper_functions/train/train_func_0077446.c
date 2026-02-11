plasma_init(char * datapath)
{
        char * finalpath;
        char mypath[] = "/data/plasma.raw";
        FILE * f;
        finalpath = malloc(strlen(datapath) + sizeof(mypath) + 1);
        if (!finalpath)
                fb__out_of_memory();
        sprintf(finalpath, "%s%s", datapath, mypath);
        f = fopen(finalpath, "rb");
        free(finalpath);

        if (!f) {
                fprintf(stderr, "Ouch, could not open plasma.raw for reading\n");
                exit(1);
        }

        plasma = malloc(XRES * YRES);
        if (!plasma)
                fb__out_of_memory();
        if (fread(plasma, 1, XRES * YRES, f) != XRES * YRES) {
                fprintf(stderr, "Ouch, could not read %d bytes from plasma file\n", XRES * YRES);
                exit(1);
        }

        fclose(f);

        plasma_max = -1;
        for (x=0; x<XRES; x++)
                for (y=0; y<YRES; y++)
                        if (plasma[x+y*XRES] > plasma_max)
                                plasma_max = plasma[x+y*XRES];

        for (y=0; y<YRES; y++)
                for (x=0; x<XRES; x++)
                        plasma[x+y*XRES] = (plasma[x+y*XRES]*plasma_steps)/(plasma_max+1);


        plasma2 = malloc(XRES * YRES);
        if (!plasma2)
                fb__out_of_memory();
        for (i=0; i<XRES*YRES; i++)
                plasma2[i] = rand_(256) - 1;

        for (y=0; y<YRES; y++)
                for (x=0; x<XRES; x++)
                        plasma2[x+y*XRES] = (plasma2[x+y*XRES]*plasma_steps)/256;

        plasma3 = malloc(XRES * YRES);
        if (!plasma3)
                fb__out_of_memory();
}
