phy_write(int location, u16 phy_data)
{
 u16 i, phy_addr=1;
 u32 io_dcr9;

 whereami("phy_write\n");

 io_dcr9 = ioaddr + CSR9;


 for (i=0; i<34; i++)
   phy_write_1bit(io_dcr9, PHY_DATA_1);


 phy_write_1bit(io_dcr9, PHY_DATA_0);
 phy_write_1bit(io_dcr9, PHY_DATA_1);


 phy_write_1bit(io_dcr9, PHY_DATA_0);
 phy_write_1bit(io_dcr9, PHY_DATA_1);


 for (i=0x10; i>0; i=i>>1)
   phy_write_1bit(io_dcr9, phy_addr&i ? PHY_DATA_1: PHY_DATA_0);


 for (i=0x10; i>0; i=i>>1)
   phy_write_1bit(io_dcr9, location&i ? PHY_DATA_1: PHY_DATA_0);


 phy_write_1bit(io_dcr9, PHY_DATA_1);
 phy_write_1bit(io_dcr9, PHY_DATA_0);


 for (i=0x8000; i>0; i>>=1)
   phy_write_1bit(io_dcr9, phy_data&i ? PHY_DATA_1: PHY_DATA_0);
}
