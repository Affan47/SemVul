printhms( const Real t )

{
    int   h,
          m;
    Real T, s;
    Real min = 60.,
	  hrs = 3600.;

    h = (int)(t/hrs);
    T = t - ((Real)h)*hrs;
    m = (int)(T/min);
    s = T - ((Real)m)*min;

    if (h == 0) {
        if (m == 0)
            fprintf(logFile,       "%.2fs",       s );
        else
            fprintf(logFile,    "%dm %05.2fs",    m, s );
    } else {
            fprintf(logFile, "%dh %02dm %05.2fs", h, m, s );
    }
}
