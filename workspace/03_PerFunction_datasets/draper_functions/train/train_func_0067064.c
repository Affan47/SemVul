draw_digital(g15canvas *canvas)
{
    unsigned int col = 0;
    unsigned int len=0;
    int narrows=0;
    int totalwidth=0;
    char buf[10];
    char ampm[3];
    int height = G15_LCD_HEIGHT - 1;

    time_t currtime = time(NULL);

    memset(buf,0,10);
    memset(ampm,0,3);
    if(showdate) {
        char buf2[40];
        strftime(buf2,40,"%A %e %B %Y",localtime(&currtime));
        g15r_renderString (canvas,(unsigned char *)buf2 , 0, G15_TEXT_MED, 80-((strlen(buf2)*5)/2), height-6);
        height-=10;
      }

    if(mode) {
   	strftime(buf,6,"%H:%M",localtime(&currtime));
    } else {
        strftime(buf,6,"%l:%M",localtime(&currtime));
	strftime(ampm,3,"%p",localtime(&currtime));
    }
    if(buf[0]==49)
    	narrows=1;

    len = strlen(buf);
    if(buf[0]==' ')
     len++;

    if(narrows)
        totalwidth=(len*20)+(15);
    else
        totalwidth=len*20;

    for (col=0;col<len;col++)
      {
      	int num = -1;
	if ((buf[col] > 47) && (buf[col] < 59))
	  num = buf[col] - 48;
	else if (buf[col] == 45)
	  num = 11;
	else if (buf[col] == 46)
	  num = 12;

	if (num >= 0)
	  g15r_drawBigNum (canvas, (80-(totalwidth)/2)+col*20, 1,(80-(totalwidth)/2)+(col+1)*20, height, G15_COLOR_BLACK, num);
      }

    if(ampm[0]!=0)
      g15r_renderString (canvas,(unsigned char *)ampm,0,G15_TEXT_LARGE,totalwidth+15,height-6);

    return G15_PLUGIN_OK;
}
