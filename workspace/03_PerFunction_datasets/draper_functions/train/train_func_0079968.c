SEC_sync_colors(AW_window *aww, AW_CL cl_mode, AW_CL) {


    int mode = (int)cl_mode;

    if (mode & 1) {
        AW_copy_GCs(aww->get_root(), "ARB_EDIT4", "ARB_SECEDIT", false,
                    "User1",   "User2",   "Probe",
                    "Primerl", "Primerr", "Primerg",
                    "Sigl",    "Sigr",    "Sigg",
                    "MISMATCHES",
                    NULL);
    }
    if (mode & 2) {
        AW_copy_GCs(aww->get_root(), "ARB_EDIT4", "ARB_SECEDIT", false,
                    "RANGE_0", "RANGE_1", "RANGE_2",
                    "RANGE_3", "RANGE_4", "RANGE_5",
                    "RANGE_6", "RANGE_7", "RANGE_8",
                    "RANGE_9",
                    NULL);
    }
    if (mode & 4) {
        AW_copy_GCs(aww->get_root(), "ARB_EDIT4", "ARB_SECEDIT", false,
                    "CURSOR",
                    NULL);
    }
}
