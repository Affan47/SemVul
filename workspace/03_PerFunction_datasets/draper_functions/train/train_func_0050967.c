Flush_Output (Object port) {
    Check_Output_Port (port);
    if (PORT(port)->flags & P_STRING)
        return;
    if (fflush (PORT(port)->file) == EOF) {
        Saved_Errno = errno;
        Primitive_Error ("write error on ~s: ~E", port);
    }
}
