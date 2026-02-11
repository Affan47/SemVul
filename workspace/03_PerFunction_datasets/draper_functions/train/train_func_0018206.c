P_Create_Cursor (Object srcp, Object maskp, Object x, Object y,
                               Object f, Object b) {
    Pixmap sp = Get_Pixmap (srcp), mp;
    Display *d = PIXMAP(srcp)->dpy;

    mp = EQ(maskp, Sym_None) ? None : Get_Pixmap (maskp);
    return Make_Cursor (d, XCreatePixmapCursor (d, sp, mp,
        Get_Color (f), Get_Color (b), Get_Integer (x), Get_Integer (y)));
}
