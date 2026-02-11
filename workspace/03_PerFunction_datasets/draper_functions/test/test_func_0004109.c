rhine_irq ( struct nic *nic, irq_action_t action ) {
    struct rhine_private *tp = (struct rhine_private *) nic->priv_data;

    unsigned int intr_status;

    switch ( action ) {
        case DISABLE :
        case ENABLE :
            intr_status = inw(nic->ioaddr + IntrStatus);


            if( tp->chip_revision < 0x80 && tp->chip_revision >=0x40 )
                intr_status |= inb(nic->ioaddr + IntrStatus2) << 16;
                intr_status = (intr_status & ~DEFAULT_INTR);
                if ( action == ENABLE )
                    intr_status = intr_status | DEFAULT_INTR;
                    outw(intr_status, nic->ioaddr + IntrEnable);
                break;
        case FORCE :
            outw(0x0010, nic->ioaddr + 0x84);
           break;
        }
}
