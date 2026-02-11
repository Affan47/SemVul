Mapper68_StateRestore(int version)
{
              if(!(mapbyte2[0]&0x10))
              {
               switch(mapbyte2[0]&3)
               {
                case 0:MIRROR_SET(0);break;
                case 1:MIRROR_SET(1);break;
                case 2:onemir(0);break;
                case 3:onemir(1);break;
               }
              }
              else if(VROM_size)
              {
		Fixerit();
                PPUNTARAM=0;
              }
}
