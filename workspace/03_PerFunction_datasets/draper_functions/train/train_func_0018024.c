P_Newline (int argc, Object *argv) {
    General_Print_Object (Newline, argc == 1 ? argv[0] : Curr_Output_Port, 1);
    return Void;
}
