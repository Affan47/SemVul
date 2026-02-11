PS_annotation_init( FL_IMAGE * im )
{
    const char *mbuf[ MBUFLEN ];
    int i,
        j,
        k,
        out;
    FLIMAGE_MARKER *m;

    if ( ! im->nmarkers && !im->ntext )
        return;

    flps_output( "/M {moveto} BD /G {setgray} BD /RGB {setrgbcolor} BD\n" );
    flps_output( "/LT {lineto} BD /L {M LT} BD /S {stroke} BD /F {fill} BD\n" );
    flps_output( "/L {M LT} BD /S {stroke} BD /F {fill} BD\n" );
    flps_output( "/LW {setlinewidth} BD /C {closepath} BD\n" );

    memset( mbuf, 0, MBUFLEN );

    if ( im->nmarkers )
    {
        flps_output( "%%marker defs: t w h angle xo yo\n" );
        flps_output( 0 );
        flps_output( "/DTD {[5 4 1 4] 0 setdash} BD\n" );
        flps_output( "/DT {[1 3] 0 setdash} BD\n" );
        flps_output( "/LD {[8 5] 0 setdash} BD\n" );
        flps_output( "/DS {[4 4] 0 setdash} BD\n" );
        flps_output( "/SL {[] 0 setdash} BD\n" );
        flps_output( "/NP {newpath} BD\n" );

        flps_output( "/BM {gsave} D /EM {grestore} D\n" );
        flps_output( "/MK {newpath translate rotate scale LW} BD\n" );


        for ( k = 0, m = im->marker, i = 0; i < im->nmarkers; i++, m++ )
        {
            for ( j = out = 0; ! out && j < MBUFLEN; j++ )
                out = m->name == mbuf[ j ];
            if ( ! out )
            {
                mbuf[ k++ ] = m->name;
                flps_output( "/%s {%s %s} D\n", m->name, "MK", m->psdraw );
            }
        }
    }

    if ( im->ntext )
    {


        flps_output( "/point {xscale yscale add 2 div div} BD\n" );
        flps_output( "/SetFont {findfont exch scalefont setfont} BD\n" );
        flps_output( "/CP {currentpoint} BD /SW {stringwidth} BD\n" );
        flps_output( "/Lshow {show} BD\n" );
        flps_output( "/Cshow {dup SW pop -2 div 0 rmoveto show} BD\n" );
        flps_output( "/Rshow {dup SW pop neg 0 rmoveto show} BD\n" );
    }
}
