g2_open_X11X(int width, int height,
		 int x, int y,
		 char *window_name, char *icon_name,
		 char *icon_data, int icon_width, int icon_height)
{
    g2_X11_device *xout=NULL;
    int pid=-1, i;
    char name[32];
    int vid;

    if(g2_X11_dev==NULL) {
	g2_X11_dev=g2_malloc(sizeof(g2_X11_device));
	N_X11=1;
	xout=&g2_X11_dev[N_X11-1];
	pid=0;
    } else {
	for(i=0;i<N_X11;i++)
	    if(g2_X11_dev[i].display==NULL) {
		xout=&g2_X11_dev[i];
		pid=i;
		break;
	    }
	if(i==N_X11) {
	    N_X11++;
	    g2_X11_dev=g2_realloc(g2_X11_dev,
				  sizeof(g2_X11_device)*N_X11);
	    xout=&g2_X11_dev[N_X11-1];
	    pid=N_X11-1;
	}
    }

    xout->width=width;
    xout->height=height;

    xout->NofInks=0;
    xout->inks=NULL;

    vid = g2_register_physical_device(pid, NULL,
				      g2_IntCoor, g2_X11_funix,
				      1.0, -1.0,
				      0.0, height-1);

    sprintf(name, "g2: %d", vid);
    if(window_name==NULL)
	window_name=name;
    if(icon_name==NULL)
	icon_name=name;

    g2_X11_init_X11X(pid, width, height,
		     x, y,
      		     window_name, icon_name,
		     icon_data, icon_width, icon_height);


    g2_allocate_basic_colors(vid);
    g2_set_background(vid, 0);
    g2_pen(vid, 1);

    return vid;
}
