idt77105_stop(struct atm_dev *dev)
{
	struct idt77105_priv *walk, *prev;

        DPRINTK("%s(itf %d): stopping IDT77105\n",dev->type,dev->number);


	PUT( GET(MCR) & ~IDT77105_MCR_EIP, MCR );


	for (prev = NULL, walk = idt77105_all ;
             walk != NULL;
             prev = walk, walk = walk->next) {
            if (walk->dev == dev) {
                if (prev != NULL)
                    prev->next = walk->next;
                else
                    idt77105_all = walk->next;
	        dev->phy = NULL;
                dev->dev_data = NULL;
                kfree(walk);
                break;
            }
        }

	return 0;
}
