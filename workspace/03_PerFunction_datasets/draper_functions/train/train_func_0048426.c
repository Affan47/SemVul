main(int argc,char **argv)
{
    Display
        *display;

    int
        status;

    XColor
        color;

    Colormap
        cmap;

    int
        i,
        r,
        g,
        b;

    for (i=1; i < argc; i++)
    {
        if (strncmp(argv[i],"-h",2) == 0)
        {
            (void) fprintf (stderr,"grabc 1.1 by Muhammad A Muquit\n");
            exit(1);
        }
    }
    display=XOpenDisplay((char *) NULL);
    cmap=DefaultColormap(display,DefaultScreen(display));

    XSetErrorHandler(MXError);

    if (display == (Display *) NULL)
    {
        (void) fprintf (stderr,"Failed to open local DISPLAY!'n");
        exit(1);
    }

    status=getWindowColor(display,&color);
    if (status == True)
    {
        XQueryColor(display,cmap,&color);
        r=(color.red >> 8);
        g=(color.green >> 8);
        b=(color.blue >> 8);
        (void) fprintf (stdout,"#%02x%02x%02x\n",r,g,b);
        (void) fflush(stdout);


        (void) fprintf(stderr,"%d,%d,%d\n",r,g,b);
    }
    else
    {
        (void) fprintf (stderr,"Failed to grab color!\n");
    }
    return (0);
}
