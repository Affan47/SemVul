P_Draw_Segments (Object d, Object gc, Object v) {
    Display *dpy;
    Drawable dr = Get_Drawable (d, &dpy);
    register XSegment *p;
    register int i, n;
    Alloca_Begin;

    Check_Type (gc, T_Gc);
    n = VECTOR(v)->size;
    Alloca (p, XSegment*, n * sizeof (XSegment));
    for (i = 0; i < n; i++) {
        Object seg;

        seg = VECTOR(v)->data[i];
        Check_Type (seg, T_Pair);
        if (Fast_Length (seg) != 4)
            Primitive_Error ("invalid segment: ~s", seg);
        p[i].x1 = Get_Integer (Car (seg)); seg = Cdr (seg);
        p[i].y1 = Get_Integer (Car (seg)); seg = Cdr (seg);
        p[i].x2 = Get_Integer (Car (seg)); seg = Cdr (seg);
        p[i].y2 = Get_Integer (Car (seg));
    }
    XDrawSegments (dpy, dr, GCONTEXT(gc)->gc, p, n);
    Alloca_End;
    return Void;
}
