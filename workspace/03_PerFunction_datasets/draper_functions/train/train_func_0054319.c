MET_SwapByteIfSystemMSB(void* val, MET_ValueEnumType _type)
    {
    if(!MET_SystemByteOrderMSB())
      {
      return;
      }

    int eSize;
    MET_SizeOfType(_type, &eSize);
    switch(eSize)
      {
      default:
      case 0:
      case 1:
        {
        break;
        }
      case 2:
        {
        MET_ByteOrderSwap2(val);
        break;
        }
      case 4:
        {
        MET_ByteOrderSwap4(val);
        break;
        }
      case 8:
        {
        MET_ByteOrderSwap8(val);
        break;
        }
      }
    }
