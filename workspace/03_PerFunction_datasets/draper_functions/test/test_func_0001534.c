ooQ931SetKeypadIE(OOCTXT* pctxt, Q931Message *pmsg, const char* data)
{
   unsigned len = 0;


   len = strlen(data);
   pmsg->keypadIE = (Q931InformationElement*)
                      memAlloc(pctxt, sizeof(Q931InformationElement)+len-1);
   if(!pmsg->keypadIE)
   {
      OOTRACEERR1("Error:Memory - ooQ931SetKeypadIE - keypadIE\n");
      return OO_FAILED;
   }

   pmsg->keypadIE->discriminator = Q931KeypadIE;
   pmsg->keypadIE->length = len;
   memcpy(pmsg->keypadIE->data, data, len);
   return OO_OK;
}
