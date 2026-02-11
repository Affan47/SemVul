smc_phy_configure(int ioaddr)
{
    int timeout;
    byte phyaddr;
    word my_phy_caps;
    word my_ad_caps;
    word status;
    int failed = 0;
    int rpc_cur_mode = RPC_DEFAULT;
    int lastPhy18;


    if (!smc_detect_phy(ioaddr, &phyaddr))
    {
        return;
    }


    smc_write_phy_register(ioaddr, phyaddr, PHY_CNTL_REG, PHY_CNTL_RST);


    timeout = 6;
    while (timeout--)
    {
        if (!(smc_read_phy_register(ioaddr, phyaddr, PHY_CNTL_REG)
              & PHY_CNTL_RST))
        {

            break;
        }

        mdelay(500);
    }

    if (timeout < 1)
    {
        PRINTK2("PHY reset timed out\n");
        return;
    }


    lastPhy18 = smc_read_phy_register(ioaddr, phyaddr, PHY_INT_REG);


    smc_write_phy_register(ioaddr, phyaddr, PHY_MASK_REG,
                           PHY_INT_LOSSSYNC | PHY_INT_CWRD | PHY_INT_SSD |
                                   PHY_INT_ESD | PHY_INT_RPOL | PHY_INT_JAB |
                                   PHY_INT_SPDDET | PHY_INT_DPLXDET);


    SMC_SELECT_BANK(ioaddr, 0);
    outw( rpc_cur_mode, ioaddr + RPC_REG );


    my_phy_caps = smc_read_phy_register(ioaddr, phyaddr, PHY_STAT_REG);
    my_ad_caps  = PHY_AD_CSMA;

    if (my_phy_caps & PHY_STAT_CAP_T4)
        my_ad_caps |= PHY_AD_T4;

    if (my_phy_caps & PHY_STAT_CAP_TXF)
        my_ad_caps |= PHY_AD_TX_FDX;

    if (my_phy_caps & PHY_STAT_CAP_TXH)
        my_ad_caps |= PHY_AD_TX_HDX;

    if (my_phy_caps & PHY_STAT_CAP_TF)
        my_ad_caps |= PHY_AD_10_FDX;

    if (my_phy_caps & PHY_STAT_CAP_TH)
        my_ad_caps |= PHY_AD_10_HDX;


    smc_write_phy_register(ioaddr, phyaddr, PHY_AD_REG, my_ad_caps);

    PRINTK2("phy caps=%x\n", my_phy_caps);
    PRINTK2("phy advertised caps=%x\n", my_ad_caps);


    smc_write_phy_register( ioaddr, phyaddr, PHY_CNTL_REG,
                            PHY_CNTL_ANEG_EN | PHY_CNTL_ANEG_RST );


    timeout = 20;
    while (timeout--)
    {
        status = smc_read_phy_register(ioaddr, phyaddr, PHY_STAT_REG);
        if (status & PHY_STAT_ANEG_ACK)
        {

            break;
        }

        mdelay(500);


        if (status & PHY_STAT_REM_FLT)
        {
            PRINTK2("PHY remote fault detected\n");


            PRINTK2("PHY restarting auto-negotiation\n");
            smc_write_phy_register( ioaddr, phyaddr, PHY_CNTL_REG,
                                    PHY_CNTL_ANEG_EN | PHY_CNTL_ANEG_RST |
                                    PHY_CNTL_SPEED | PHY_CNTL_DPLX);
        }
    }

    if (timeout < 1)
    {
        PRINTK2("PHY auto-negotiate timed out\n");
        failed = 1;
    }


    if (status & PHY_STAT_REM_FLT)
    {
        PRINTK2("PHY remote fault detected\n");
        failed = 1;
    }


    if ( lastPhy18 & PHY_INT_SPDDET )
    {
        PRINTK2("PHY 100BaseT\n");
        rpc_cur_mode |= RPC_SPEED;
    }
    else
    {
        PRINTK2("PHY 10BaseT\n");
        rpc_cur_mode &= ~RPC_SPEED;
    }

    if ( lastPhy18 & PHY_INT_DPLXDET )
    {
        PRINTK2("PHY Full Duplex\n");
        rpc_cur_mode |= RPC_DPLX;
    }
    else
    {
        PRINTK2("PHY Half Duplex\n");
        rpc_cur_mode &= ~RPC_DPLX;
    }


    outw( rpc_cur_mode, ioaddr + RPC_REG );
}
