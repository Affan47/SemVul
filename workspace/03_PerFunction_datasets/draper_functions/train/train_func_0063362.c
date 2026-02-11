P_Get_Gc_Values (Object gc) {
    unsigned long mask = ValidGCValuesBits;

    Check_Type (gc, T_Gc);
    if (!XGetGCValues (GCONTEXT(gc)->dpy, GCONTEXT(gc)->gc, mask, &GCV))
        Primitive_Error ("cannot get gcontext values");
    return Record_To_Vector (GC_Rec, GC_Size, Sym_Gc, GCONTEXT(gc)->dpy,
        mask);
}
