P_Grab_Keyboard (Object win, Object ownerp, Object psyncp,
                               Object ksyncp, Object time) {
    Check_Type (win, T_Window);
    Check_Type (ownerp, T_Boolean);
    return Bits_To_Symbols ((unsigned long)XGrabKeyboard (WINDOW(win)->dpy,
            WINDOW(win)->win, EQ(ownerp, True), Get_Mode (psyncp),
            Get_Mode (ksyncp), Get_Time (time)),
        0, Grabstatus_Syms);
}
