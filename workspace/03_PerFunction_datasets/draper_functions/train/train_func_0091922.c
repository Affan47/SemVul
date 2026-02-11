UNIFGI(int h)
{
 switch(h)
 {
  case GI_RESETM2:
                if(UNIFCart.Reset)
                 UNIFCart.Reset();
		break;
  case GI_POWER:
                if(UNIFCart.Power)
                 UNIFCart.Power();
		if(UNIFchrrama) memset(UNIFchrrama,0,8192);
		break;
  case GI_CLOSE:
                FCEU_SaveGameSave(&UNIFCart);
		if(UNIFCart.Close)
		 UNIFCart.Close();
                FreeUNIF();
                break;
 }
}
