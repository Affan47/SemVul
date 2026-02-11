maxmtu2maxsdu(uint8_t mtu)
{

    int sdu;

    switch (mtu) {
    case MTU_1516:
        sdu = 1516;
        break;
    case MTU_1580:
        sdu = 1580;
        break;
    case MTU_4544:
        sdu = 4544;
        break;
    case MTU_9234:
        sdu = 9234;
        break;
    case MTU_18190:
        sdu = 18190;
        break;
    default:
        sdu = 1516;
        break;
    }

    return sdu;
}
