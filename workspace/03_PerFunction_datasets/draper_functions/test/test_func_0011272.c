ColorString(REAL r, REAL g, REAL b) const{
    if (s_betterConsole)
        return s_betterConsole->ColorString(r,g,b);
    else
        return tString("");
}
