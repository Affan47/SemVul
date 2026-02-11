set_body(void* bodyPtr)
{
   if( button_type == BUTTON_TEXT )
   {
      int strLen = strlen((char*)bodyPtr);

      if( strLen > STR_BUF_LEN )
         strLen = STR_BUF_LEN;

      memcpy( str_buf, bodyPtr, strLen );
      str_buf[strLen] = '\0';
   }
   else
      body_ptr = bodyPtr;
}
