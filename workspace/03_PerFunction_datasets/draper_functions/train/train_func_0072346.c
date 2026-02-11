Set_Prio (int priority)
{
    const char *data;
    long length;
    Atom atom, type;
    thunk *thunks;
    int size, fsize;
    const char *prop="_NET_WM_PID";
    const char *format = NULL;
    const char *dformat = NULL;
    atom = XInternAtom(dpy, prop, True);

    if (atom == None) {
	printf(":  no such atom on any window.\n");
	return;
    }

    data = Get_Window_Property_Data_And_Type(atom, &length, &type, &size);
    if (!size) {
	puts(":  not found.");
	return;
    }


    Lookup_Formats(atom, &format, &dformat);
    if (type != None)
	Lookup_Formats(type, &format, &dformat);
    Apply_Default_Formats(&format, &dformat);

    fsize = Get_Format_Size(format);
    if (fsize != size && fsize != 0) {
	printf(": Type mismatch: assumed size %d bits, actual size %d bits.\n",
	       fsize, size);
	return;
    }

    thunks = Break_Down_Property(data, (int)length, type, format, size);

    Set_Display_Priority(thunks, dformat, format, priority);
}
