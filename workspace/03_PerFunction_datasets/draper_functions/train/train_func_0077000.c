DXLHandlePendingMessages(DXLConnection *conn)
{

   DXLProcessEventList(conn);
   while (_dxl_IsReadable(conn))
   {
       _dxl_ReadFromSocket(conn);
       DXLProcessEventList(conn);
   }

   return OK;
}
