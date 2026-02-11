P_Chown(Object fn, Object uid, Object gid) {
#ifndef WIN32
    if (chown(Get_Strsym(fn), Get_Integer(uid), Get_Integer(gid)) == -1)
        Raise_System_Error1("~s: ~E", fn);
#endif
    return Void;
}
