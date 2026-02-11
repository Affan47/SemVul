CERT_CopyAVA(PLArenaPool *arena, CERTAVA *from)
{
    CERTAVA *ava;
    int rv;

    ava = (CERTAVA*) PORT_ArenaZAlloc(arena, sizeof(CERTAVA));
    if (ava) {
	rv = SECITEM_CopyItem(arena, &ava->type, &from->type);
	if (rv) goto loser;
	rv = SECITEM_CopyItem(arena, &ava->value, &from->value);
	if (rv) goto loser;
    }
    return ava;

  loser:
    return 0;
}
