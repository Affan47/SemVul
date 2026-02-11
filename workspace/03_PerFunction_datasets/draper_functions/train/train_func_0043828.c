isMatchingTile(POSITION &Pos1, POSITION &Pos2)
{

    if (memcmp(&Pos1, &Pos2, sizeof(POSITION))) {
        UCHAR FA = Pos1.f;
        UCHAR FB = Pos2.f;

        if ((FA == FB) || (isFlower(FA) && isFlower(FB)) || (isSeason(FA) && isSeason(FB))) {
            return true;
        }
    }

    return false;
}
