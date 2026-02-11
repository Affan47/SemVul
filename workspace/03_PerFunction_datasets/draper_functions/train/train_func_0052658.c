drawYLegend(cairo_t *cr, double temp_max, double temp_min, int width, int height)
{
    double range = temp_max - temp_min;
    int one_degree_height = (height-Y1_SKIP-Y2_SKIP)/10;
    int i;
    char tstring[10];

    for(i=0;i<10;i++)
    {
        cairo_move_to(cr, X1_SKIP-TICK_OFFSET, one_degree_height*i+Y2_SKIP);
        cairo_line_to(cr, width-X2_SKIP ,one_degree_height*i+Y2_SKIP);
        cairo_stroke(cr);


        sprintf(tstring,"%d",(int)(temp_max-(range/10)*i));
        cairo_move_to(cr ,X1_SKIP-X1_TO_TEXT, one_degree_height*i+Y2_SKIP);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 9.0);
        cairo_show_text(cr, tstring);
    }
}
