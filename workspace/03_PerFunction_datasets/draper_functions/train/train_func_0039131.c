hrZoneColor(int z, int) {
    switch(z) {

    case 0  : return GColor(CHZONE1); break;
    case 1  : return GColor(CHZONE2); break;
    case 2  : return GColor(CHZONE3); break;
    case 3  : return GColor(CHZONE4); break;
    case 4  : return GColor(CHZONE5); break;
    case 5  : return GColor(CHZONE6); break;
    case 6  : return GColor(CHZONE7); break;
    case 7  : return GColor(CHZONE8); break;
    case 8  : return GColor(CHZONE9); break;
    case 9  : return GColor(CHZONE10); break;
    default: return QColor(128,128,128); break;
    }
}
