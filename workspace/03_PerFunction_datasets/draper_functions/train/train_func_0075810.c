checkType (const string &varname, const Value &val, Type t, const char *typen, Object *obj) {
    if (val.type != T_NONE) {
        if (val.type != t) {
            if (!checkenum (val, t) && (val.type & t & 1) == 0) {
                runtimeError ("Can't assign this value (%s) to %s, it has a different type (%s)", typen, varname.c_str(), typestring (val).c_str()) ;
            }
        } else if (val.type == T_OBJECT) {
            if (val.object != NULL && obj != NULL) {
                Block *varblk = val.object->block ;
                Block *valblk = obj->block ;
                if (!blocksCompatible (varblk, valblk)) {
                    runtimeError ("Can't assign this value (%s) to %s, it has a different type (%s)", typen, varname.c_str(), typestring (val).c_str()) ;
                }
            }

        }

    }
}
