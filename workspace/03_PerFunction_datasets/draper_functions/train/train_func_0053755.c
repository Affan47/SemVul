setvar (tnk_t tnk, Tobj vo) {
    switch (tnk.type) {
    case TNK_LI:
        Mresetmark (
            lvarp[flvari + tnk.u.li].m, (lvarp[flvari + tnk.u.li].o = vo)
        );
        break;
    case TNK_O:
        Tinso (tnk.u.tnko.to, tnk.u.tnko.ko, vo);
        break;
    default:
        switch (tnk.u.tnks.kt) {
        case C_STRING:
            Tinss (
                tnk.u.tnks.to, TCgetstring (tnk.u.tnks.co, tnk.u.tnks.vi), vo
            );
            break;
        case C_INTEGER:
            Tinsi (
                tnk.u.tnks.to, TCgetinteger (tnk.u.tnks.co, tnk.u.tnks.vi), vo
            );
            break;
        case C_REAL:
            Tinsr (tnk.u.tnks.to, TCgetreal (tnk.u.tnks.co, tnk.u.tnks.vi), vo);
            break;
        }
        break;
    }
}
