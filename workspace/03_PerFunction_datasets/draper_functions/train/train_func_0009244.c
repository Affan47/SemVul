pssetlineattr			(GtkPlotPC *pc,
                                                 gfloat line_width,
                                                 GdkLineStyle line_style,
                                                 GdkCapStyle cap_style,
                                                 GdkJoinStyle join_style)
{
    FILE *psout = GTK_PLOT_PS(pc)->psfile;

    fprintf(psout, "%g slw\n", line_width);
    fprintf(psout, "%d slc\n", abs(cap_style - 1));
    fprintf(psout, "%d slj\n", join_style);

    if(line_style == 0)
            fprintf(psout,"[] 0 sd\n");
}
