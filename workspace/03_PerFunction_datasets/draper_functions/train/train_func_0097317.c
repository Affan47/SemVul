parse_other (packetinfo *pi)
{
    update_asset(pi);

    if (pi->cxt->check == 0x00) {
        if (IS_COSET(&config,CO_OTHER)) {
            pi->cxt->check = 0x01;


        } else {
            vlog(0x3, "[*] - NOT CHECKING *OTHER* PACKAGE\n");
        }
    }
}
