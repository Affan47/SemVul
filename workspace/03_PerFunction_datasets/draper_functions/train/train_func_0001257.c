FetchData( IDirectFBDataBuffer *buffer, void *data, unsigned int len )
{
     DFBResult ret = DFB_OK;

     do {
          unsigned int read = 0;

          ret = buffer->WaitForData( buffer, len );
          if (ret == DFB_OK)
               ret = buffer->GetData( buffer, len, data, &read );
          if (ret)
               break;

          data += read;
          len  -= read;
     } while (len);

     return ret;
}
