ftesl_get_ctrlcode(TKeyCode key)
{
        TKeyCode        kcode = keyCode(key);

        switch(kcode) {
            case kbUp:     return FTESL_KBDCTRL('u');
            case kbDown:   return FTESL_KBDCTRL('d');
            case kbLeft:   return FTESL_KBDCTRL('l');
            case kbRight:  return FTESL_KBDCTRL('r');
            case kbCenter: return FTESL_KBDCTRL('x');
            case kbHome:   return FTESL_KBDCTRL('b');
            case kbEnd:    return FTESL_KBDCTRL('e');
            case kbPgUp:   return FTESL_KBDCTRL('p');
            case kbPgDn:   return FTESL_KBDCTRL('n');
            case kbIns:    return FTESL_KBDCTRL('q');
            case kbDel:    return FTESL_KBDCTRL('z');
            case kbBackSp: return FTESL_KBDCTRL('h');
            case kbTab:    return FTESL_KBDCTRL('i');
            case kbEnter:  return FTESL_KBDCTRL('m');
        }
        if (kcode>=kbF1 && kcode<=kbF12) return FTESL_KBDCTRL('f');
        else return (int)kcode;

}
